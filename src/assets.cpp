//
//  assets.cpp
//  until_dawn_screen_2
//
//  Created by miguel on 16/07/15.
//
//

#include "assets.h"
Assets::Assets(){
}

Assets* Assets::instance = 0;

Assets* Assets::getInstance(){
    if (instance == 0){
        instance = new Assets();
        instance->load();
    }
    
    return instance;
};


void Assets::load(){
    
    
    string filename = "wireframe.png";
    wireframe.loadImage(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    for(int i = 0; i < 5; i ++){
        string filename = "glitch_" + ofToString(i) + ".mov";
        glitches[i].loadMovie(filename);
        ofLogNotice() << "Loading: " << filename ;
    }
    
    
    for(int i = 0; i < 64; i++)
        fonts[i] = NULL;
    
}

float Assets::getScale(){
    return WW / 1920.0;
}

ofTrueTypeFont *Assets::getFont(float size){
    int i = int(size * getScale());
    if(fonts[i] == NULL){
        fonts[i] = new ofTrueTypeFont();
        fonts[i]->loadFont("Akkurat-Mono.ttf", i, true, true, true);
        fonts[i]->setLetterSpacing(1.1);
        fonts[i]->setSpaceSize(0.3);
        
        ofLogNotice() << "Loading: " << "Akkurat-Mono.ttf " << i;
    }
    return fonts[i];
}

int Assets::getWidth(){
    if(ofGetWindowWidth() < ofGetWindowHeight())
        return ofGetWindowWidth();
    else
        return ofGetWindowHeight();
}


int Assets::getHeight(){
    if(ofGetWindowWidth() < ofGetWindowHeight())
        return ofGetWindowHeight();
    else
        return ofGetWindowWidth();
}
