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
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    camWidth 		= 640;
    camHeight 		= 480;
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    setupFluids();
    
    lastTime = ofGetElapsedTimef();
    
    
    for(int i = 0; i < FLOW_SIZE; i ++){
        flow.push_back(0);
        flow_x.push_back(0);
        flow_y.push_back(0);
    }
}

void FlowEngine::updateFlow(){
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        img.setFromPixels(vidGrabber.getPixelsRef());
        img.crop(0, 0, camWidth , camWidth * 450 / 910.);
        
        colorImg.setFromPixels(img.getPixelsRef());
        gray = colorImg;
        
        inverted = gray;
        inverted.invert();
        thresh.setFromPixels(inverted.getPixelsRef());
        ofxCv::threshold(thresh, 150);
        
        thresh.update();
        
        contourFinder.findContours(thresh);
        updateFluids();
        computeFlow();
    }
}

void FlowEngine::computeFlow(){
    
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
    
    ofxJSONElement response;
    response.open("http://localhost:3000/flow.json?v=" + ofToString(avgFlow));
    
}

void FlowEngine::setupFluids(){
    
    flowWidth = camWidth/4;
    flowHeight = camWidth * 450 / 910;
    
    
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