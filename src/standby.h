//
//  standby.h
//  until_dawn_screen_1
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_1__standby__
#define __until_dawn_screen_1__standby__

#include <State.h>

class Standby: public State
{
    
public:
    Standby(App *g);
    ~Standby(){};
    std::string toString() { return "stand by"; }
    void update();
    void draw();
    void next();
};



#endif /* defined(__until_dawn_screen_1__standby__) */
