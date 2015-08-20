//
//  flowGlitch.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__flowGlitch__
#define __until_dawn_screen_3__flowGlitch__
#include <State.h>

class flowGlitch: public State
{
    ofVideoPlayer video;
    
public:
    flowGlitch(App *g);
    ~flowGlitch(){};
    std::string toString() { return "flowGlitch"; }
    void update();
    void draw();
    void next();
    
    
};

#endif /* defined(__until_dawn_screen_3__flowGlitch__) */
