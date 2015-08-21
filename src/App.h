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


class App
{
    
public:
    App();
    class State *current_state;
    
    ofxOscReceiver *receiver;
    
    void setCurrentState(State *s);
    void keyPressed(ofKeyEventArgs& eventArgs);
    void update(ofEventArgs &args);
    
    void update();
    void next();
    void jump();
    void draw();
    void cancel();
};


#endif /* defined(__until_dawn_screen_3__App__) */
