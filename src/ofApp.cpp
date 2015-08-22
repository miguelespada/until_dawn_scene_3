#include "ofApp.h"
#include "standby.h"
#include "thermal.h"
#include "flow.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(8);
    
    assets = Assets::getInstance();
    
    bRotated = true;
    setRotation();
    

    
    app.setCurrentState(new Thermal(&app));
    
//    setFullScreen();
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

    //ofSaveScreen("image_" + ofToString(ofGetFrameNum()) + ".jpg");

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
            
        case 'R':
            bRotated = !bRotated;
            setRotation();
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

void ofApp::setFullScreen(){
    ofSetWindowPosition(1921, 0);
    ofToggleFullscreen();
    bRotated = false;
    setRotation();

}