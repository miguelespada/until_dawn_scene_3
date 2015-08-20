#include "ofApp.h"
#include "standby.h"
#include "thermal.h"
#include "flow.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //    ofToggleFullscreen();
    ofSetFrameRate(12);
    
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
    
    app.draw();
    ofPopMatrix();

//   ofSaveScreen("image_" + ofToString(ofGetFrameNum()) + ".jpg");

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
        ofSetWindowShape(1080 * assets->getScale(), 1920 * assets->getScale());
    else
        ofSetWindowShape(1920 * assets->getScale(), 1080 * assets->getScale());
}