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
};

void Standby::draw(){
    int w = Assets::getInstance()->getWidth();
    int h = Assets::getInstance()->getHeight();
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(30);
    
    string msg = "STAND BY";
    
    int text_x = w / 2 - font->stringWidth(msg) / 2;
    font->drawString(msg, text_x, h/4 + font->stringHeight(msg) * 1.5);
    
    
    
};

void Standby::update(){
    processOsc();
}


void Standby::next(){
    app->setCurrentState(new Thermal(app));
    delete this;
};

void Standby::processOsc(){
    while(app->receiver->hasWaitingMessages()){
        ofxOscMessage m;
        app->receiver->getNextMessage(&m);
    }
}
