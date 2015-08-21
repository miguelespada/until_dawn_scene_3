#include "ofApp.h"
#include "standby.h"
#include "thermal.h"
#include "flow.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowPosition(1921, 0);
    ofSetFrameRate(12);
    
    assets = Assets::getInstance();
    
    bRotated = false;
    setRotation();
    
    
    ofVideoGrabber 		vidGrabber;
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    
    app.setCurrentState(new Flow(&app));
    
    
    ofToggleFullscreen();

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