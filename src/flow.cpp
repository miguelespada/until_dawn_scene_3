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
#include "flowGlitch.h"
#include "ofxJSON.h"


Flow::Flow(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    assets = Assets::getInstance();
    
    
    flowEngine = app->flowEngine;
//    flowEngine->resetFlow();
    
    timer = ofGetElapsedTimef();
    
};

void Flow::draw(){
    
    flowEngine = app->flowEngine;
    try
    {
         flowEngine->gray.draw(84, 200, 910,  450);
        flowEngine->inverted.draw(84, 784, 910,  450);
        
            
        //        inverted.draw(84, 784, 910,  450);
        //        thresh.draw(84, 784, 910,  450);
        //        thresh.draw(84, 1366, 910,  450);

            drawContours();
            drawFluids();
    }
    
    catch (int e)
    {
        ofLogError() << "An exception occurred. Exception Nr. " << e;
    }
    
    assets->wireframe_flow.draw(0, 0);
    
    
    string msg;
    ofTrueTypeFont *font = assets->getFont(11);
    
    msg = "INFRARED CAMERA";
    font->drawStringAsShapes(msg, 84, 177 + font->getLineHeight() / 1.5);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "CONTOURS";
    font->drawStringAsShapes(msg, 84, 758 + font->getLineHeight() / 1.5);
    
    msg = "OPTICAL FLOW";
    font->drawStringAsShapes(msg, 84, 1344 + font->getLineHeight() / 1.5);
    
    int n = ofGetFrameNum() / 10;
    if(n % 3 == 0)
        msg = "PROCESANDO.";
    if(n % 3 == 1)
        msg = "PROCESANDO..";
    if(n % 3 == 2)
        msg = "PROCESANDO...";
    
    font->drawStringAsShapes(msg, 855, 177 + font->getLineHeight() / 1.5);
    
    drawOpticalValue();
};

void Flow::update(){    
    if(ofGetElapsedTimef() - timer  > 16)
        next();
}


void Flow::next(){
    app->setCurrentState(new thermalGlitch(app));
    delete this;
};


void Flow::drawFluids(){
    ofPushMatrix();
    ofTranslate(84, 1366);
    flowEngine->velocityField.setSource(flowEngine->fluid.getVelocity());
    flowEngine->velocityField.draw(0, 0, 910,  450);
    ofPopMatrix();
}

void Flow::drawContours(){
    ofPushMatrix();
    ofTranslate(84, 784);
    ofSetLineWidth(1);
    ofScale(910 / flowEngine->thresh.getWidth(), 450 / flowEngine->thresh.getHeight(), 1);
    flowEngine->contourFinder.draw();
    ofPopMatrix();
    
    
    ofPushMatrix();
    
    ofTranslate(965 , 853 );
    string msg;
    msg = ofToString( flowEngine->contourFinder.size() );
    
    ofTrueTypeFont *font = assets->getFont(30);
    font->drawStringAsShapes(msg,  - font->stringWidth(msg), 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "CONTOUR SIZE";
    font->drawStringAsShapes(msg, - font->stringWidth(msg), 0);
    
    ofPopMatrix();

    
}

void Flow::drawOpticalValue(){
  
    
    ofPushMatrix();
    
    ofTranslate(965 , 273 );
    string msg;
    msg = ofToString(int(flowEngine->flow[flowEngine->flow.size() - 1] * 10000) / 100.);
    
    ofTrueTypeFont *font = assets->getFont(30);
    font->drawStringAsShapes(msg,  - font->stringWidth(msg), 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "OPTICAL VALUE";
    font->drawStringAsShapes(msg, - font->stringWidth(msg), 0);
    
    ofPopMatrix();

    
    int s = 150;
    ofPushMatrix();
    ofTranslate(890, 550) ;
    ofSetColor(255);
    ofSetLineWidth(1);
    
    ofNoFill();
    ofRect(-s/2, - s/2, s, s);
    for(int i = 0; i < FLOW_SIZE; i += 10)
        ofLine(0, 0, flowEngine->flow_x[i] * s, flowEngine->flow_y[i] * s);
    
    ofPopStyle();
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(120, 550 + s / 2) ;
    ofSetColor(assets->blue);
    ofSetLineWidth(1);
    
    
    ofScale(2, 1);
    for(int i = 1; i < FLOW_SIZE; i ++)
        ofLine(i - 1, - flowEngine->flow[i - 1] * s, i, -flowEngine->flow[i] * s);
    
    
    ofSetColor(255);
    ofPopStyle();
    ofPopMatrix();

}



