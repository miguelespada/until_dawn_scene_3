//
//  termal.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__termal__
#define __until_dawn_screen_3__termal__

#include <State.h>
#include "assets.h"

#define BUFFER_SIZE 20

class Thermal: public State
{
    
    Assets *assets;
    
    ofVideoGrabber 		vidGrabber;
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    
    ofImage img;
    vector<ofImage> images;
    
    int delta_y;
    bool bSave;
    
public:
    Thermal(App *g);
    ~Thermal(){};
    std::string toString() { return "Thermal"; }
    void update();
    void draw();
    void next();
    void processOsc();
    
    void drawElapsedTime(int x, int y);
    float initial_time;
};


#endif /* defined(__until_dawn_screen_3__termal__) */
