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
#include "standby.h"



Thermal::Thermal(App *a){
    app = a;
    ofLogNotice() << "State: " << toString();
    
    assets = Assets::getInstance();
    
    initial_time = ofGetElapsedTimef();
    
    
    thermalEngine = app->thermalEngine;
    
    timer = ofGetElapsedTimef();

};

void Thermal::draw(){
    if(thermalEngine->hasImages()){
        
        thermalEngine->prev(19).draw(84, 200, 910,  450);
        thermalEngine->prev(9).draw(84, 784, 910,  450);
        thermalEngine->lastImage().draw(84, 1366, 910,  450);
    }
    
    drawElapsedTime();
    drawTexts();
    drawThermalData();
    drawTemperature();
    drawTarget();
    
    assets->wireframe_thermal.draw(0, 0);
    
};


void Thermal::update(){
    
    if( ofGetElapsedTimef() > timer + 16)
        next();
}


void Thermal::next(){
    app->setCurrentState(new flowGlitch(app));
    delete this;
};


void Thermal::drawElapsedTime(){
    ofPushMatrix();
    
    ofTranslate(818 , 273);
    int elapsed_seconds = app->data["runningTime"].asInt();
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
    
    msg = app->data["name"].asString();
    font->drawStringAsShapes(msg, 84, 177 + font->getLineHeight() / 1.5);
    
    msg = ofToString(ofGetFrameRate());
    
    msg = "THERMAL BALANCE";
    font->drawStringAsShapes(msg, 84, 758 + font->getLineHeight() / 1.5);
}

void Thermal::drawTarget(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(84, 1366);
    
    ofLine(910. * thermalEngine->target_x, 0, 910. * thermalEngine->target_x,  450);
    ofLine(0, 450. * thermalEngine->target_y, 910., 450. * thermalEngine->target_y);
    
    ofNoFill();
    ofTranslate(910. * thermalEngine->target_x, 450. * thermalEngine->target_y);
    ofRect(-20, -20, 40, 40);
    ofPopStyle();
    ofPopMatrix();
    
    
    
    ofTrueTypeFont *font  = assets->getFont(16);
    string  msg = "(" + ofToString(ofToString(int(thermalEngine->target_x * 100) / 100.) + "," + ofToString(int(thermalEngine->target_y * 100) / 100.)) + ")";
    font->drawStringAsShapes(msg, 964 - font->stringWidth(msg),  1388 + font->getLineHeight() / 1.5);

}


void Thermal::drawThermalVariation(){
    
    ofPushMatrix();
    ofTranslate(800, 900);
    
    ofScale(1.5, 30);
    
    float var = 0;
    
    for(int i = 1; i < thermalEngine->dist.size(); i ++){
        float d0 = thermalEngine->dist[i-1];
        float d1 = thermalEngine->dist[i];
        ofLine(i - 1, - d0, i, - d1 );
    }
    
    ofPopMatrix();
    
    ofTrueTypeFont *font  = assets->getFont(16);
    string msg = "HUE VARIANCE";
    font->drawStringAsShapes(msg, 964 - font->stringWidth(msg), 843 + font->getLineHeight() / 1.5);
   
    
    font = assets->getFont(24);
    
    msg = ofToString(int(thermalEngine->avg * 10));
    
    font->drawStringAsShapes(msg, 964 - font->stringWidth(msg),  804 + font->getLineHeight() / 1.5);

}

void Thermal::drawThermalData(){
    drawThermalVariation();
}

void Thermal::drawTemperature(){
    
    ofxJSONElement temps = app->data["temp"];
    temperature = temps[temps.size() - 1].asFloat() / 100.;
    
    float y = ofMap(temperature, 26., 42., 1022, 806);
    
    ofLine(105, y, 110, y);
    
    
    ofLine(783, 1107, 783, 1197);
    ofLine(783, 1197, 962, 1197);
    
    ofPushMatrix();
    ofTranslate(786, 1197);
    ofScale(0.9, 1);
    for(int i = 0; i < temps.size() / 5; i += 1){
        float t =  temps[i].asFloat() / 100;
        
        if(t < 30) t = 36.5;
        
        float y = ofMap(t, 30., 40., 0, 90);
        
        ofLine(i*5, 0, i*5, - y);
    }
    ofPopMatrix();
}