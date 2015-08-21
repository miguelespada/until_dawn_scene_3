//
//  termal.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#include "thermal.h"

#include "standby.h"
#include "flowGlitch.h"
#include "App.h"
#include "Assets.h"



Thermal::Thermal(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    assets = Assets::getInstance();
    
    camWidth 		= 640;
    camHeight 		= 480;
    
    vidGrabber.setDeviceID(1);
    vidGrabber.initGrabber(camWidth, camHeight);

    delta_y = 0;
    bSave = false;
    images = vector<ofImage>();
    
    initial_time = ofGetElapsedTimef();
    
};

void Thermal::draw(){
    int w = assets->getWidth();
    int h = assets->getHeight();
    
    if(vidGrabber.isFrameNew()){
        img.setFromPixels(vidGrabber.getPixelsRef());
        img.crop(0, delta_y, camWidth , camWidth * 450 / 910.);
        
        if(bSave)
            ofSaveImage(img, "image_" + ofToString(ofGetFrameNum()) + ".jpg");
        
        images.push_back(img);
    }
    
    if(images.size() > BUFFER_SIZE)
        images[images.size() - (BUFFER_SIZE + 1)].draw(84 * assets->getScale(), 200 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
    else if(img.isAllocated())
        img.draw(84 * assets->getScale(), 200 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
    
    if(images.size() > BUFFER_SIZE / 2)
        images[images.size() - (BUFFER_SIZE/2 + 1)].draw(84 * assets->getScale(), 784 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
    else if(img.isAllocated())
        img.draw(84 * assets->getScale(), 784 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
    
    if(images.size() > 0)
        images[images.size() - 1].draw(84 * assets->getScale(), 1366 * assets->getScale(), 910 * assets->getScale(),  450 * assets->getScale());
    
    if(images.size() > BUFFER_SIZE)
        images.erase(images.begin()+ 0);
    
    
    assets->wireframe.draw(0, 0, w, h);
    
    string msg;
    ofTrueTypeFont *font = assets->getFont(11);
    
    msg = "MIGUEL V. ESPADA";
    font->drawString(msg, 84 * assets->getScale(), 177 * assets->getScale() + font->getLineHeight() / 1.5);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "TERMAL BALANCE";
    font->drawString(msg, 84 * assets->getScale(), 758 * assets->getScale() + font->getLineHeight() / 1.5);
    
    drawElapsedTime(818  * assets->getScale(), 273  * assets->getScale());
    
};

void Thermal::update(){
    vidGrabber.update();
}

void Thermal::processOsc(){
    while(app->receiver->hasWaitingMessages()){
        ofxOscMessage m;
        app->receiver->getNextMessage(&m);
        
        if(m.getAddress() == "/delta"){
            delta_y = m.getArgAsInt32(0);
        }
    }
}


void Thermal::next(){
    app->setCurrentState(new flowGlitch(app));
    delete this;
};

void Thermal::drawElapsedTime(int x, int y){
    ofPushMatrix();
    
    ofTranslate(x, y);
    int elapsed_seconds = int(ofGetElapsedTimef() - initial_time /1000);
    int elapsed_minutes = elapsed_seconds / 60;
    elapsed_seconds %= 60;
    string leading_minutes = "";
    if(elapsed_minutes < 10)
        leading_minutes = "0";
    
    string leading_seconds = "";
    if(elapsed_seconds < 10)
        leading_seconds = "0";
    string msg;
    msg = leading_minutes + ofToString(elapsed_minutes) + ":" + leading_seconds + ofToString(elapsed_seconds);
    
    ofTrueTypeFont *font = assets->getFont(30);
    font->drawString(msg, 0, 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "TRANSCURRIDO";
    font->drawString(msg, 0, 0);
    
    ofPopMatrix();
    
}
