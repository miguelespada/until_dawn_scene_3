#include "App.h"
#include "ofxJSON.h"
#include "assets.h"


App::App(){
    // Register events and actions
    ofAddListener(ofEvents().keyPressed, this, &App::keyPressed);
    ofAddListener(ofEvents().update, this, &App::update);
    
    receiver = new ofxOscReceiver;
    receiver->setup(12345);
    
    
    ofLogNotice() << "App... ";
    
    flowEngine = new FlowEngine();
    thermalEngine = new ThermalEngine();
    
    flowEngine->setupCamera();
    thermalEngine->setupCamera();
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
    
    try
    {
        current_state->update();
        flowEngine->updateFlow();
        thermalEngine->updateThermal();
    }
    
    catch (int e)
    {
        ofLogError() << "An exception occurred. Exception Nr. " << e;
    }
    
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        receiver->getNextMessage(&m);
        
        if(m.getAddress() == "/delta"){
            thermalEngine->delta_y = m.getArgAsInt32(0);
        }
    }

}

void App::update(ofEventArgs &args){
    update();
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

