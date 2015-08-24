//
//  index.h
//  until_dawn_screen_1
//
//  Created by miguel on 19/08/15.
//
//

#ifndef __until_dawn_screen_1__index__
#define __until_dawn_screen_1__index__

#include <State.h>

class Index: public State
{
    
public:
    Index(App *g);
    ~Index(){};
    std::string toString() { return "index"; }
    void update();
    void draw();
    void next();
};


#endif /* defined(__until_dawn_screen_1__index__) */
