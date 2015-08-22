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
    
    filename = "eye.png";
    eye.loadImage(filename);
    ofLogNotice() << "Loading: " << filename;
    
    filename = "parametros.png";
    parametros.loadImage(filename);
    ofLogNotice() << "Loading: " << filename;
    
    
    for(int i = 0; i < 5; i ++){
        string filename = "glitch_" + ofToString(i) + ".mov";
        glitches[i].loadMovie(filename);
        ofLogNotice() << "Loading: " << filename ;
    }
    
    for(int i = 0; i < 64; i++)
        fonts[i] = NULL;
    
}


ofTrueTypeFont *Assets::getFont(int size){
    if(fonts[size] == NULL){
        fonts[size] = new ofTrueTypeFont();
        fonts[size]->loadFont("Akkurat-Mono.ttf", size, true, true, true);
        fonts[size]->setLetterSpacing(1.1);
        fonts[size]->setSpaceSize(0.3);
        
        ofLogNotice() << "Loading: " << "Akkurat-Mono.ttf " << size;
    }
    return fonts[size];
}
