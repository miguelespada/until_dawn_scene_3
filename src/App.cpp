#include "App.h"
#include "ofxJSON.h"
#include "assets.h"


App::App(){
    ofAddListener(ofEvents().keyPressed, this, &App::keyPressed);
    ofAddListener(ofEvents().update, this, &App::update);
    
    receiver = new ofxOscReceiver;
    receiver->setup(12345);
    
    
    ofLogNotice() << "App... ";
    
    flowEngine = new FlowEngine();
    thermalEngine = new ThermalEngine();
    
    flowEngine->setupCamera();
    thermalEngine->setupCamera();
    
    
    if(BLACKMAGIC)
        cam.setup(1920, 1080, 30);
}

App::~App(){
    cam.close();
    delete flowEngine;
    delete thermalEngine;
}


void App::setCurrentState(State *s){
    current_state = s;
}

void App::next(){
    current_state->next();
}

void App::jump(){
    current_state->jump();
}

void App::cancel(){
    current_state->cancel();
}

void App::draw(){
    ofPushStyle();
    ofPushMatrix();
    current_state->draw();
    ofPopMatrix();
    ofPopStyle();
}

void App::update(){
    if(BLACKMAGIC){
        
        if(current_state->toString() == "Thermal")
            updateBlackMagic();
    }
    try
    {
        current_state->update();
    
        flowEngine->updateFlow();
        if(current_state->toString() == "Thermal")
            thermalEngine->updateThermal(blackMagicImage);
    }
    
    catch (int e)
    {
        ofLogError() << "An exception occurred. Exception Nr. " << e;
    }
    
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        receiver->getNextMessage(&m);
        if(m.getAddress() == "/thermal"){
            thermalEngine->delta_y = m.getArgAsInt32(0);
            thermalEngine->target_x = m.getArgAsFloat(1);
            thermalEngine->target_y = m.getArgAsFloat(2);
        }
    }

}

void App::update(ofEventArgs &args){
    update();
    
    
    if(ofGetFrameNum() % 15 == 0){
        data.open("http://localhost:3000/last.json");
    }
}

void App::keyPressed (ofKeyEventArgs& eventArgs){
    switch (eventArgs.key) {
        case 'n':
            next();
            break;
        default:
            break;
    }
}

void App::updateBlackMagic(){
    if(cam.update()){
        blackMagicImage.setFromPixels(cam.getColorPixels());
    }
    
}

