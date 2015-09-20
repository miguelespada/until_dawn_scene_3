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
#include "ofxJSON.h"
#include "pbNetwork.h"

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
    
    
    void update();
    void next();
    void jump();
    void draw();
    void cancel();
    void processOsc();
    
    FlowEngine *flowEngine;
    ThermalEngine *thermalEngine;
    ofVideoGrabber webCam;
    ofVideoPlayer heatVideo;
    
    ofxJSONElement data;
    bool bSave;
    void save();
    string dir;
    
    void setupNetwork();
    void receiveHeatmap();
    
    pbNetworkReceiver _receiver;	//Network receiver
    int _frameId;		//id of received frame
    
    int w, h;			//Width and height of image
    int size;			//Size of image data in bytes
    
    ofImage heatMapImage;		//Received image
    
    //FPS counter
    float _receiveLastTime;
    int _receiveCount;
    float _receiveFPS;

};


#endif /* defined(__until_dawn_screen_3__App__) */
