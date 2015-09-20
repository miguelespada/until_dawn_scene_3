#include "ofApp.h"
#include "standby.h"
#include "thermal.h"
#include "flow.h"

#include "standby.h"
#include "index.h"
#include "calculandoIndex.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(10);
    
    assets = Assets::getInstance();
    
    bRotated = true;
    setRotation();
    
    app.setCurrentState(new Thermal(&app));
}

//--------------------------------------------------------------
void ofApp::update(){
 }

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(0);
    
    ofPushMatrix();
    
    if(!bRotated){
        ofTranslate(0, ofGetHeight());
        ofRotate(-90);
    }
    
    if(ofGetWindowWidth() < ofGetWindowHeight())
        ofScale(ofGetWidth() / 1080., ofGetHeight() / 1920. );
    else
        ofScale(ofGetWidth() / 1920., ofGetHeight() / 1080. );
    
    app.draw();
    ofPopMatrix();
    
    if (app.bSave){
//        string filename = app.dir + "/" + ofToString(ofGetTimestampString()) + ".jpg";
        string f = "";
        if(frame < 100000)
            f += "0";
        if(frame < 10000)
            f += "0";
        if(frame < 1000)
            f += "0";
        if(frame < 100)
            f += "0";
        if(frame < 10)
            f += "0";
        f += ofToString(frame);
        
        string filename = app.dir + "/" + f + ".jpg";
        frame++;
        ofSaveScreen(filename);
        ofLogNotice() << "Saving... " << filename;
    }
    if(ofGetFrameNum() % 30 == 0)
        ofLogNotice() << ofGetFrameRate();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
            
        case 'R':
            bRotated = !bRotated;
            setRotation();
            break;
            
        case 'S':
            app.bSave = !app.bSave;
            app.save();
            break;
            
        case 'i':
            app.current_state->standby();
            break;
        case '=':
            app.current_state->index();
            break;
        case '0':
            
            app.current_state->calculandoIndex();
            break;
            
        case 'F':
            setFullScreen(true);
            break;
        case 'f':
            setFullScreen(false);
            break;
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
void ofApp::setRotation(){
    
    if(bRotated)
        ofSetWindowShape(HH, WW);
    else
        ofSetWindowShape(WW, HH);
}


void ofApp::setFullScreen(bool bFull){
    if(bFull){
        ofSetFullscreen(true);
        bRotated = false;
        setRotation();
        ofSetWindowShape(1920, 1080);
        ofSetWindowPosition(0, 0);
        ofHideCursor();
    }
    else{
        ofSetWindowPosition(100, 100);
        ofSetFullscreen(false);
        bRotated = true;
        setRotation();
        ofShowCursor();
    }
    
}