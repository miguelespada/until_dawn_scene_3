//
//  App.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__App__
#define __until_dawn_screen_3__App__

#include "ofMain.h"
#include "State.h"
#include "ofxOsc.h"
#include "flowEngine.h"
#include "thermalEngine.h"
#include "ofxBlackMagic.h"
#include "ofxJSON.h"

class App
{
    
public:
    App();
    ~App();
    class State *current_state;
    
    ofxOscReceiver *receiver;
    
    void setCurrentState(State *s);
    void keyPressed(ofKeyEventArgs& eventArgs);
    void update(ofEventArgs &args);
    
    void updateBlackMagic();
    
    void update();
    void next();
    void jump();
    void draw();
    void cancel();
    void processOsc();
    
    FlowEngine *flowEngine;
    ThermalEngine *thermalEngine;
    
    ofxBlackMagic cam;
    ofImage blackMagicImage;
    
    
    ofxJSONElement data;
    bool bSave;
    void save();
    string dir;
};


#endif /* defined(__until_dawn_screen_3__App__) */
