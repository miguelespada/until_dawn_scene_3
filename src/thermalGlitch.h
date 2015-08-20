//
//  thermalGlitch.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__thermalGlitch__
#define __until_dawn_screen_3__thermalGlitch__

#include <State.h>

class thermalGlitch: public State
{
    ofVideoPlayer video;
    
public:
    thermalGlitch(App *g);
    ~thermalGlitch(){};
    std::string toString() { return "thermalGlitch"; }
    void update();
    void draw();
    void next();
    
    
};

#endif /* defined(__until_dawn_screen_3__thermalGlitch__) */
