#include "App.h"
#include "ofxJSON.h"
#include "assets.h"
#include "standby.h"


App::App(){
    ofAddListener(ofEvents().keyPressed, this, &App::keyPressed);
    ofAddListener(ofEvents().update, this, &App::update);
    
    receiver = new ofxOscReceiver;
    receiver->setup(12343);
    
    
    ofLogNotice() << "App... ";
    
    flowEngine = new FlowEngine();
    thermalEngine = new ThermalEngine();
    
    flowEngine->setupCamera();
    thermalEngine->setupCamera();
    
    
    if(BLACKMAGIC)
        cam.setup(1920, 1080, 30);
    
    bSave = false;
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
    
        if(current_state->toString() == "Thermal" || current_state->toString() == "Flow"){
            flowEngine->updateFlow();
        
            if(current_state->toString() == "Thermal")
                thermalEngine->updateThermal(blackMagicImage);
        }
    }
    
    catch (int e)
    {
        ofLogError() << "An exception occurred. Exception Nr. " << e;
    }
    
    
    while(receiver->hasWaitingMessages()){
        ofxOscMessage m;
        
        receiver->getNextMessage(&m);
        cout << m.getAddress() << endl;
        if(m.getAddress() == "/thermal"){
            thermalEngine->delta_x = m.getArgAsInt32(0);
            thermalEngine->delta_y = m.getArgAsInt32(1);
            thermalEngine->target_x = m.getArgAsFloat(2);
            thermalEngine->target_y = m.getArgAsFloat(3);
        }
        
        if(m.getAddress() == "/flow"){
            flowEngine->delta_y = m.getArgAsInt32(0);
        }
        
        if(m.getAddress() == "/standby"){
            current_state->standby();
        }
        
        if(m.getAddress() == "/next"){
            current_state->next();
        }
        
        
        if(m.getAddress() == "/index"){
            current_state->index();
        }
        
        if(m.getAddress() == "/calculandoIndex"){
            current_state->calculandoIndex();
        }
        
        if(m.getAddress() == "/save"){
            bSave = bool(m.getArgAsInt32(0));
            save();
        }
        
    }

}

void App::save(){
    ofLogNotice() << "Saving ---> " << bSave;
    dir = "images/" + data["_id"]["$oid"].asString();
    if(bSave && !ofDirectory::doesDirectoryExist(dir)){
        ofDirectory::createDirectory(dir, true);
        ofLogNotice() << "Creating directory: " << dir << endl;
    }
}

void App::update(ofEventArgs &args){
    update();
    
    
    if(ofGetFrameNum() % 15 == 0){
        data.open("http://192.168.1.42:3000/last.json");
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

