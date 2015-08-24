//
//  flowGlitch.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#include "flowGlitch.h"
#include "App.h"
#include "Assets.h"
#include "flow.h"

flowGlitch::flowGlitch(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    video = Assets::getInstance()->glitches[int(ofRandom(4))];
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    timer = ofGetElapsedTimef();
    
};

void flowGlitch::draw(){
    
   if(video.isLoaded())
        video.draw(0, 0);
};

void flowGlitch::update(){
    video.update();
    
    if(ofGetElapsedTimef()  > timer + 1){
        next();
    }
}

void flowGlitch::next(){
    video.stop();
    app->setCurrentState(new Flow(app));
    delete this;
    
};