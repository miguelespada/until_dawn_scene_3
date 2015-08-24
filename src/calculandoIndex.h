//
//  calculandoIndex.h
//  until_dawn_screen_1
//
//  Created by miguel on 19/08/15.
//
//

#ifndef __until_dawn_screen_1__calculandoIndex__
#define __until_dawn_screen_1__calculandoIndex__

#include <State.h>

class calculandoIndex: public State
{
    
public:
    calculandoIndex(App *g);
    ~calculandoIndex(){};
    std::string toString() { return "calculandoIndex"; }
    void update();
    void draw();
    void next();
    
    float alpha;
    int dots;
};

#endif /* defined(__until_dawn_screen_1__calculandoIndex__) */
