//
//  thermalEngine.h
//  until_dawn_screen_3
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_3__termalEngine__
#define __until_dawn_screen_3__termalEngine__

#include "ofMain.h"
#define BUFFER_SIZE 20

class ThermalEngine
{
    
public:
    //    ofVideoGrabber 		vidGrabber;
    ofVideoPlayer vidGrabber;
    
    int camWidth;
    int camHeight;
    int delta_y;

    
    ofImage img;
    ofImage img_1;
    ofImage img_2;
    vector<ofImage> images;
    vector<ofPoint> samples;
    vector<float> hues;
    vector<float> saturation;
    vector<float> bright;
    vector<float> dist;
    
    
    void calculateVariation();
    void sample();
    
    void setupCamera();
    void updateThermal();
    
    void saveThermal(float absDist);
    
    bool hasImages();
    ofImage lastImage();
    ofImage prev(int n);
    
    
};

#endif /* defined(__until_dawn_screen_3__flowEngine__) */