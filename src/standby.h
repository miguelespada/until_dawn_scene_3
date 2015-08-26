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
    ofVideoPlayer video;
    
public:
    Standby(App *g);
    ~Standby(){
        cout << "video stop" << endl;
        video.stop();
    };
    std::string toString() { return "stand by"; }
    void update();
    void draw();
    void next();
    void clear();
};



#endif /* defined(__until_dawn_screen_1__standby__) */
