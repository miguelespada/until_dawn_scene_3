//
//  thermalGlitch.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#include "thermalGlitch.h"
#include "App.h"
#include "Assets.h"
#include "thermal.h"

thermalGlitch::thermalGlitch(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    video = Assets::getInstance()->glitches[int(ofRandom(5))];
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    timer = ofGetElapsedTimef();
    
};



void thermalGlitch::draw(){
    
    if(video.isLoaded())
        video.draw(0, 0);
};

void thermalGlitch::update(){
    video.update();
    
    if(ofGetElapsedTimef()  > timer + 1){
        next();
    }
}

void thermalGlitch::next(){
    app->setCurrentState(new Thermal(app));
    delete this;
    
};