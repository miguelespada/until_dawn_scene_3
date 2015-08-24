//
//  flowEngine.h
//  until_dawn_screen_3
//
//  Created by miguel on 22/08/15.
//
//

#ifndef __until_dawn_screen_3__flowEngine__
#define __until_dawn_screen_3__flowEngine__


#include "ofMain.h"
#include "ofxFlowTools.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
using namespace flowTools;


class FlowEngine
{
    
public:
    
    void setupCamera();
    void updateFlow();
    void setupFluids();
    void updateFluids();
    void computeFlow();
    void saveFlow(float avgFlow);
    void resetFlow();
    
    ofVideoGrabber 		vidGrabber;
    int 				camWidth;
    int 				camHeight;
    
    ofImage img;
    
    ofImage thresh;
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
    
    int delta_y;
    int frames;
};

#endif /* defined(__until_dawn_screen_3__flowEngine__) */
