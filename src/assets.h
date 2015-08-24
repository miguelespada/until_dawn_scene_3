//
//  assets.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__assets__
#define __until_dawn_screen_3__assets__

#include "ofMain.h"

#define SCALE 2
#define WW 1920/SCALE
#define HH 1080/SCALE
#define FLOW_SIZE 150

#define NETWORK true

class Assets{
public:
    static Assets* getInstance();
    void load();

    
    ofVideoPlayer glitches[5];
    
    ofColor red = ofColor(231, 57, 51);
    ofColor blue = ofColor(0, 116, 188);
    ofColor yellow = ofColor(254, 223, 82);
    ofColor green = ofColor(94, 172, 77);
    ofColor orange = ofColor(243, 144, 69);
    
    
    ofImage wireframe_flow;
    ofImage wireframe_thermal;
    ofImage eye;
    ofImage parametros;
    
    ofTrueTypeFont		*fonts[64];
    ofTrueTypeFont *getFont(int size);
    
    
private:
    static Assets* instance;
    Assets();
};



#endif /* defined(__until_dawn_screen_3__assets__) */
