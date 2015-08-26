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
#include "ofxOsc.h"

#define BUFFER_SIZE 20

class ThermalEngine
{
    
    
public:
    
    int camWidth;
    int camHeight;
    int delta_y;
    int delta_x;
    
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
    void updateThermal(ofImage heatImg);
    
    void saveThermal(float absDist);
    
    bool hasImages();
    ofImage lastImage();
    ofImage prev(int n);
    
    ofxOscSender sender;
    
};

#endif /* defined(__until_dawn_screen_3__flowEngine__) */