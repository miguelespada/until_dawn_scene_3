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
    font->drawString(msg, 84 * assets->getScale(), 177 * assets->getScale() + font->getLineHeight() / 2);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "CONTOURS";
    font->drawString(msg, 84 * assets->getScale(), 758 * assets->getScale() + font->getLineHeight() / 2);
    
    msg = "OPTICAL FLOW";
    font->drawString(msg, 84 * assets->getScale(), 1344 * assets->getScale() + font->getLineHeight() / 2);
    
    int n = ofGetFrameNum() / 10;
    if(n % 3 == 0)
        msg = "PROCESANDO.";
    if(n % 3 == 1)
        msg = "PROCESANDO..";
    if(n % 3 == 2)
        msg = "PROCESANDO...";
    
    font->drawString(msg, 855 * assets->getScale(), 177 * assets->getScale() + font->getLineHeight() / 2);
    
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
}
