//
//  calculandoIndex.cpp
//  until_dawn_screen_1
//
//  Created by miguel on 17/08/15.
//
//

#include "calculandoIndex.h"
#include "App.h"
#include "Assets.h"
#include "index.h"

calculandoIndex::calculandoIndex(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    video = Assets::getInstance()->calculando;
    
    video.setLoopState(OF_LOOP_PALINDROME);
    video.setPosition(0);
    video.play();
    timer = ofGetElapsedTimef();
    alpha = 0;
    dots = 0;
};

void calculandoIndex::draw(){

    if(video.isLoaded())
        video.draw(0, 0);
    
    int w = 1080;
    int h = 1920;
    
    ofPushMatrix();
    ofTranslate(0, 100);
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(30);
    string msg = "CALCULANDO";
    
    int text_x = w / 2 - font->stringWidth(msg) / 2;
    font->drawStringAsShapes(msg, text_x, h/4);
    
    msg = "ÍNDICE UNTIL DAWN";
    
    
    text_x = w / 2 - font->stringWidth(msg) / 2;
    font->drawStringAsShapes(msg, text_x, h/4 + font->stringHeight(msg) * 1.5);
    
    string dots_msg = ".";
    for(int i = 0; i < dots; i ++)
        dots_msg += ".";
    
    font->drawStringAsShapes(dots_msg, text_x + font->stringWidth(msg) - 20 , h/4 + font->stringHeight(msg) * 1.5);
    ofPopMatrix();

};

void calculandoIndex::update(){
    
    if(video.isLoaded())
        video.update();
    
    alpha += 0.2;
    if(ofGetFrameNum() % 10 == 0)
        dots = (dots + 1) % 3;
}


void calculandoIndex::next(){
    app->setCurrentState(new Index(app));
    delete this;
};

void calculandoIndex::clear(){
    video.stop();
};