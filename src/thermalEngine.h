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
    ofVideoPlayer vidGrabber;
    
    int camWidth;
    int camHeight;
    int delta_y;
    float target_x;
    float target_y;

    float avg;
    
    ofImage img;
    ofImage img_1;
    ofImage img_2;
    vector<ofImage> images;
    
    vector<float> dist;
    
    
    void calculateVariation();
    
    void calculateAvg();
    
    void setupCamera();
    void updateThermal(ofImage blackMagicImg);
    
    void saveThermal(float absDist);
    
    bool hasImages();
    ofImage lastImage();
    ofImage prev(int n);
    
    
};

#endif /* defined(__until_dawn_screen_3__flowEngine__) */