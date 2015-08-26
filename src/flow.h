//
//  flow.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__flow__
#define __until_dawn_screen_3__flow__


#include <State.h>

#include "ofxFlowTools.h"
#include "ofxCv.h"

#include "ofxOpenCv.h"
#include "assets.h"
#include "flowEngine.h"
#include "ofxOsc.h"

class Flow: public State
{
    
    Assets *assets;
    
  
    
public:
    Flow(App *g);
    ~Flow(){};
    std::string toString() { return "Flow"; }
    void update();
    void draw();
    void next();
    void processOsc();
    
    void drawFluids();
    void drawContours();
    void drawOpticalValue();
    
    FlowEngine *flowEngine;
    
};


#endif /* defined(__until_dawn_screen_3__flow__) */
