//
//  flow.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#include "flow.h"

#include "standby.h"
#include "App.h"
#include "Assets.h"
#include "thermalGlitch.h"
#include "ofxJSON.h"


Flow::Flow(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    assets = Assets::getInstance();
    
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
};

void Flow::draw(){
    
    int w = assets->getWidth();
    int h = assets->getHeight();
    
    if(img.isAllocated()){
        inverted.draw(84 * assets->getScale(), 200 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
        
//        inverted.draw(84 * assets->getScale(), 784 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
//        thresh.draw(84 * assets->getScale(), 784 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
//        thresh.draw(84 * assets->getScale(), 1366 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());

        
   
        drawContours();
        drawFluids();
    }
    
    
    assets->wireframe.draw(0, 0, w, h);
    
    
    string msg;
    ofTrueTypeFont *font = assets->getFont(11);
    
    msg = "INFRARED CAMERA";
    font->drawString(msg, 84 * assets->getScale(), 177 * assets->getScale() + font->getLineHeight() / 1.5);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "CONTOURS";
    font->drawString(msg, 84 * assets->getScale(), 758 * assets->getScale() + font->getLineHeight() / 1.5);
    
    msg = "OPTICAL FLOW";
    font->drawString(msg, 84 * assets->getScale(), 1344 * assets->getScale() + font->getLineHeight() / 1.5);
    
    int n = ofGetFrameNum() / 10;
    if(n % 3 == 0)
        msg = "PROCESANDO.";
    if(n % 3 == 1)
        msg = "PROCESANDO..";
    if(n % 3 == 2)
        msg = "PROCESANDO...";
    
    font->drawString(msg, 855 * assets->getScale(), 177 * assets->getScale() + font->getLineHeight() / 1.5);
    
    drawOpticalValue();
};

void Flow::update(){
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

void Flow::processOsc(){
    while(app->receiver->hasWaitingMessages()){
        ofxOscMessage m;
        app->receiver->getNextMessage(&m);
    }
}


void Flow::next(){
    app->setCurrentState(new thermalGlitch(app));
    delete this;
};



void Flow::setupFluids(){
    
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

void Flow::updateFluids(){
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

void Flow::drawFluids(){
    ofPushMatrix();
    ofTranslate(84 * assets->getScale(), 1366 * assets->getScale());
    velocityField.setSource(fluid.getVelocity());
    velocityField.draw(0, 0, 910 * assets->getScale(),  450 * assets->getScale());
    ofPopMatrix();
}

void Flow::drawContours(){
    ofPushMatrix();
    ofTranslate(84 * assets->getScale(), 784 * assets->getScale());
    ofSetLineWidth(1);
    ofScale(910 * assets->getScale() / thresh.getWidth(), 450 * assets->getScale() / thresh.getHeight(), 1);
    contourFinder.draw();
    ofPopMatrix();
    
    
    ofPushMatrix();
    
    ofTranslate(965  * assets->getScale(), 853  * assets->getScale());
    string msg;
    msg = ofToString( contourFinder.size() );
    
    ofTrueTypeFont *font = assets->getFont(30);
    font->drawString(msg,  - font->stringWidth(msg), 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "CONTOUR SIZE";
    font->drawString(msg, - font->stringWidth(msg), 0);
    
    ofPopMatrix();

    
}

void Flow::drawOpticalValue(){
  
    
    ofPushMatrix();
    
    ofTranslate(965  * assets->getScale(), 273  * assets->getScale());
    string msg;
    msg = ofToString(int(flow[flow.size() - 1] * 10000) / 100.);
    
    ofTrueTypeFont *font = assets->getFont(30);
    font->drawString(msg,  - font->stringWidth(msg), 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "OPTICAL VALUE";
    font->drawString(msg, - font->stringWidth(msg), 0);
    
    ofPopMatrix();

    
    int s = 150;
    ofPushMatrix();
    ofTranslate(890 * assets->getScale(), 550 * assets->getScale()) ;
    ofSetColor(255);
    ofSetLineWidth(1);
    
    ofNoFill();
    ofRect(-s/2 * assets->getScale(), - s/2 * assets->getScale(), s * assets->getScale(), s * assets->getScale());
    for(int i = 0; i < FLOW_SIZE; i += 10)
        ofLine(0, 0, flow_x[i] * s * assets->getScale(), flow_y[i] * s * assets->getScale());
    
    ofPopStyle();
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(120 * assets->getScale(), 550 * assets->getScale() + s / 2 * assets->getScale()) ;
    ofSetColor(255);
    ofSetLineWidth(1);
    
    
    ofScale(2 * assets->getScale(), 1);
    for(int i = 1; i < FLOW_SIZE; i ++)
        ofLine(i - 1, - flow[i - 1] * s * assets->getScale(), i, - flow[i] * s * assets->getScale());
    
    ofPopStyle();
    ofPopMatrix();
    
    int w =  assets->parametros.getWidth() * assets->getScale();
    int h =  assets->parametros.getHeight() * assets->getScale();

    
    assets->parametros.draw(426 * assets->getScale(), 1735 * assets->getScale(), w, h);
}


void Flow::computeFlow(){
    
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
    
    ofxJSONElement response;
    response.open("http://localhost:3000/flow.json?v=" + ofToString(avgFlow));

    
}
