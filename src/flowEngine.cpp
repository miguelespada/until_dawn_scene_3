//
//  flowEngine.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 22/08/15.
//
//

#include "flowEngine.h"
#include "ofxJSON.h"
#include "assets.h"

void FlowEngine::setupCamera(){

    camWidth 		= 640;
    camHeight 		= 316;
    
    camera.setImageType(OF_IMAGE_GRAYSCALE);
    camera.setSize(camWidth, camHeight);
    camera.setFrameRate(10);
    camera.setBlocking(false);
    
    camera.setup();
    
    setupFluids();
    
    lastTime = ofGetElapsedTimef();
    
    
    for(int i = 0; i < FLOW_SIZE; i ++){
        flow.push_back(0);
        flow_x.push_back(0);
        flow_y.push_back(0);
    }
    delta_y = 0;
    frames  = 0;
    sender.setup("192.168.1.42", 12350);
    threshold = 50;
    contourFinder.setAutoThreshold(true);
    contourFinder.setMinArea(100);
    contourFinder.setMaxArea(10000);
    
}

void FlowEngine::resetFlow(){
    frames  = 0;
}

void FlowEngine::updateFlow(){
    if(camera.grabVideo(img)){
        gray.setFromPixels(img.getPixelsRef());
        
        inverted = gray;
        inverted.invert();
        thresh.setFromPixels(inverted.getPixelsRef());
        ofxCv::threshold(thresh, threshold);
        
        thresh.update();
        
        contourFinder.findContours(gray);
        updateFluids();
        frames ++;
        computeFlow();
    }
}

void FlowEngine::computeFlow(){
    if(frames < 2) return;
    ofVec2f *flowVectors = opticalFlow.getFlowVectors();
    
    float avgFlow_x = 0;
    float avgFlow_y = 0;
    float avgFlow = 0;
    for (int i=0; i < flowWidth * flowHeight; i++) {
        avgFlow_x += flowVectors[i].x;
        avgFlow_y += flowVectors[i].y;
        avgFlow += flowVectors[i].length();
    }
    avgFlow_x /= flowWidth * flowHeight;
    avgFlow_y /= flowWidth * flowHeight;
    avgFlow /= flowWidth * flowHeight;
    
    
    avgFlow = ofClamp(avgFlow, 0, 1);
    
    flow.push_back(avgFlow);
    flow_x.push_back(avgFlow_x);
    flow_y.push_back(avgFlow_y);
    
    
    if(flow.size() > FLOW_SIZE){
        flow.erase(flow.begin()+ 0);
        flow_x.erase(flow_x.begin()+ 0);
        flow_y.erase(flow_y.begin()+ 0);
    }
    
    
    saveFlow(avgFlow);
    
}

void FlowEngine::saveFlow(float avgFlow){
    
    float t = ofGetElapsedTimeMillis();
    ofxOscMessage m;
    m.setAddress("/flow");
    m.addFloatArg(avgFlow);
    sender.sendMessage(m);
    
}

void FlowEngine::setupFluids(){
    
    flowWidth = camWidth/4;
    flowHeight = camHeight/4;
    
    
    // Flow & Mask
    opticalFlow.setup(flowWidth, flowHeight);
    velocityMask.setup(flowWidth, flowHeight);
    
    // Fluid
    fluid.setup(flowWidth, flowHeight, flowWidth, flowHeight, true);
    
    // Particles
    particleFlow.setup(flowWidth, flowHeight, flowWidth, flowHeight);
    
    // Visualisation
    velocityField.allocate(flowWidth / 4, flowHeight / 4);
    
    cameraFbo.allocate(flowWidth, flowHeight);
    cameraFbo.clear();
    
    lastTime = ofGetElapsedTimef();
}

void FlowEngine::updateFluids(){
    velocityField.setVectorSize(0.2);
    
    cameraFbo.begin();
    thresh.draw(0, 0, cameraFbo.getWidth(), cameraFbo.getHeight());
    cameraFbo.end();
    
    opticalFlow.setSource(cameraFbo.getTextureReference());
    opticalFlow.update(0);
    
    velocityMask.setDensity(cameraFbo.getTextureReference());
    velocityMask.setVelocity(opticalFlow.getOpticalFlow());
    velocityMask.update();
    
    fluid.addVelocity(opticalFlow.getOpticalFlowDecay());
    fluid.addDensity(velocityMask.getColorMask());
    fluid.addTemperature(velocityMask.getLuminanceMask());
    
    fluid.update();
}