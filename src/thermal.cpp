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
    
    initial_time = ofGetElapsedTimef();
    
    
    thermalEngine = app->thermalEngine;

};

void Thermal::draw(){
    
    if(thermalEngine->hasImages()){
        
        thermalEngine->prev(20).draw(84, 200, 910,  450);
        thermalEngine->prev(10).draw(84, 784, 910,  450);
        thermalEngine->lastImage().draw(84, 1366, 910,  450);
    }
    
    if(thermalEngine->images.size() > 0)
        thermalEngine->images[thermalEngine->images.size() - 1].draw(84, 1366, 910,  450);
    
    

    

    drawTexts();
    drawThermalData();
    drawElapsedTime();
    
    
    assets->wireframe.draw(0, 0);
};



void Thermal::update(){
}


void Thermal::next(){
    app->setCurrentState(new flowGlitch(app));
    delete this;
};

void Thermal::drawElapsedTime(){
    ofPushMatrix();
    
    ofTranslate(818 , 273);
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
    font->drawStringAsShapes(msg, 0, 0);
    
    ofTranslate(0, - font->getLineHeight() * 0.9);
    font = assets->getFont(12);
    msg = "TRANSCURRIDO";
    font->drawStringAsShapes(msg, 0, 0);
    
    ofPopMatrix();
    
}

void Thermal::drawTexts(){
    string msg;
    ofTrueTypeFont *font = assets->getFont(11);
    
    msg = "MIGUEL V. ESPADA";
    font->drawStringAsShapes(msg, 84, 177 + font->getLineHeight() / 1.5);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "THERMAL BALANCE";
    font->drawStringAsShapes(msg, 84, 758 + font->getLineHeight() / 1.5);
}

void Thermal::drawSamples(){
    
    ofTrueTypeFont *font  = assets->getFont(12);
    string msg = "HUE AVG";
    font->drawStringAsShapes(msg, 815, 1730);
    
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(815, 1600);
    
    ofSetLineWidth(0.5);
    for(int i = 0; i < 9; i ++){
        ofLine(0, i * 10 , 160, i * 10);
        ofLine(i * 20, 0, i * 20, 80);
    }
    
    ofSetLineWidth(1);
    
    ofScale(0.25, 0.25);
    
    for(int i = 0; i < 100; i ++){
        int x = thermalEngine->samples[i].x;
        int y = thermalEngine->samples[i].y;
        ofNoFill();
        ofEllipse(x, y, 10 , 10 );
        
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void Thermal::drawHue(){
    
    ofPushMatrix();
    
    ofTranslate(825, 1950);
    
    ofScale(1.4, 1);
    for(int i = 1; i < thermalEngine->hues.size(); i ++){
        float h0 = thermalEngine->hues[i - 1];
        float h1 = thermalEngine->hues[i];
        if(h0 != 0 && h1 != 0)
            ofLine(i - 1, - h0, i, - h1);
    }
    
    ofPopMatrix();
    
    
}
void Thermal::drawThermalVariation(){
    
    ofTrueTypeFont *font  = assets->getFont(12);
    string msg = "HUE VARIANCE";
    font->drawStringAsShapes(msg, 257, 1178 + font->getLineHeight() / 1.5);
    
    
    ofPushMatrix();
    ofTranslate(257, 1165);
    
    ofScale(4, 2);
    
    
    for(int i = 1; i < thermalEngine->dist.size(); i ++){
        float d0 = thermalEngine->dist[i-1];
        float d1 = thermalEngine->dist[i];
        
        ofLine(i - 1, - d0, i, - d1 );
    }
    
    ofPopMatrix();
   
    
    float d = thermalEngine->dist[thermalEngine->dist.size() - 1];
    msg = ofToString(d);
    
    font->drawStringAsShapes(msg, 257, 1198 + font->getLineHeight() / 1.5);
    
}

void Thermal::drawThermalData(){
    drawSamples();
    drawHue();
    
    drawThermalVariation();

    
    

    

    
    
    
}
