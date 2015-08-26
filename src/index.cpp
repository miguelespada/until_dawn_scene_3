//
//  index.cpp
//  until_dawn_screen_1
//
//  Created by miguel on 19/08/15.
//
//

#include "index.h"
#include "App.h"
#include "Assets.h"

Index::Index(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    user.open("http://192.168.1.42:3000/last.json");
    
    
    video = computeIndiceVideo(user);
    video.play();
    video.setLoopState(OF_LOOP_PALINDROME);
    
};

void Index::draw(){
    if(video.isLoaded())
        video.draw(0, 0);
  
    
    int w = 1080;
    int h = 1920;
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(30);
    
    string msg = user["name"].asString();
    
    int text_x = w / 2 - font->stringWidth(msg) / 2;
    font->drawStringAsShapes(msg, text_x, h/4 + font->stringHeight(msg) * 1.5);
    
};

void Index::update(){
    video.update();
    
}

void Index::next(){
};

ofVideoPlayer Index::computeIndiceVideo(ofxJSONElement top){
    if(top["indice"].asInt() > 90)
        return Assets::getInstance()->indices[4];
    else if (top["indice"].asInt() > 70)
        return Assets::getInstance()->indices[3];
    else if (top["indice"].asInt() > 50)
        return Assets::getInstance()->indices[2];
    else if (top["indice"].asInt() > 25)
        return Assets::getInstance()->indices[1];
    else
        return Assets::getInstance()->indices[0];
    
}

void Index::clear(){
    video.stop();
};
