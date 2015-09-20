//
//  standby.cpp
//  until_dawn_screen_1
//
//  Created by miguel on 20/08/15.
//
//

#include "standby.h"
#include "App.h"
#include "Assets.h"
#include "thermal.h"

Standby::Standby(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    Assets::getInstance()->stopVideos();
    
    video = Assets::getInstance()->standby;
    video.play();
    video.setLoopState(OF_LOOP_NORMAL);
    
};

void Standby::draw(){
    if(video.isLoaded())
        video.draw(0, 0);
};

void Standby::update(){
    
    if(video.isLoaded())
        video.update();

}


void Standby::next(){
    app->setCurrentState(new Thermal(app));
    delete this;
};

void Standby::clear(){
    if(video.isLoaded())
        video.stop();
};