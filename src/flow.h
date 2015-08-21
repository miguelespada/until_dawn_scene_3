//
//  flow.h
//  until_dawn_screen_3
//
//  Created by miguel on 20/08/15.
//
//

#ifndef __until_dawn_screen_3__flow__
#define __until_dawn_screen_3__flow__


#include <State.h>

#include "ofxFlowTools.h"
#include "ofxCv.h"

#include "ofxOpenCv.h"
#include "assets.h"

#include "ofxGui.h"

using namespace flowTools;

#define FLOW_SIZE 150

class Flow: public State
{
    
    Assets *assets;
    
    ofVideoGrabber 		vidGrabber;
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    
    ofImage img;
    
    
    ofImage thresh;
    ofImage orig;
    ofVideoPlayer player;
    ofxCvGrayscaleImage gray;
    ofxCvGrayscaleImage inverted;
    ofxCvColorImage colorImg;
    ofxCv::ContourFinder contourFinder;
    
    
    // Camera
    ftFbo				cameraFbo;
    
    // Time
    float				lastTime;
    
    // FlowTools
    int					flowWidth;
    int					flowHeight;
    
    ftOpticalFlow		opticalFlow;
    ftVelocityMask		velocityMask;
    ftFluidSimulation	fluid;
    ftParticleFlow		particleFlow;
    
    ftDisplayScalar		displayScalar;
    ftVelocityField		velocityField;
    ftTemperatureField	temperatureField;
    
    vector<float> flow;
    vector<float> flow_x;
    vector<float> flow_y;
  
    
public:
    Flow(App *g);
    ~Flow(){};
    std::string toString() { return "Flow"; }
    void update();
    void draw();
    void next();
    void processOsc();
    void setupFluids();
    void updateFluids();
    void drawFluids();
    void drawContours();
    void drawOpticalValue();
    void computeFlow();
    
    
};


#endif /* defined(__until_dawn_screen_3__flow__) */
