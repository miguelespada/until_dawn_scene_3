//
//  flowEngine.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 22/08/15.
//
//

#include "thermalEngine.h"
#include "ofxJSON.h"
#include "assets.h"

void ThermalEngine::setupCamera(){
    camWidth 		= 640;
    camHeight 		= 480;
    //
    //    vidGrabber.setDeviceID(1);
    //    vidGrabber.initGrabber(camWidth, camHeight);
    //
    
    images = vector<ofImage>();
    
    
    vidGrabber.loadMovie("carlos.mp4");
    vidGrabber.play();
    sample();
    
    for(int i = 0; i < 100; i ++){
        hues.push_back(0);
        saturation.push_back(0);
        bright.push_back(0);
        dist.push_back(0);
    }

}

void ThermalEngine::updateThermal(){

    
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        img.setFromPixels(vidGrabber.getPixelsRef());
        img.crop(0, delta_y, camWidth , camWidth * 450 / 910.);
        
        images.push_back(img);
        
        if(images.size() > 0)
            calculateVariation();
        
        
        if(images.size() > BUFFER_SIZE)
            images.erase(images.begin());
    }
    

    
    if(ofGetFrameNum() % 20 == 0)
        sample();
}


void ThermalEngine::sample(){
    samples.clear();
    for(int i = 0; i < 100; i ++){
        int x = ofRandom(camWidth);
        int y = ofRandom(camWidth * 450 / 910.);
        samples.push_back(ofPoint(x, y));
    }
    
}

void ThermalEngine::calculateVariation(){

    float h = 0;
    float h_1 = 0;
    float s = 0;
    float b = 0;
    
    for(int i = 0; i < 100; i ++){
        int x = samples[i].x;
        int y = samples[i].y;

        ofColor c = img.getColor(x, y);
        h += c.getHueAngle();
        
        ofColor c1 = prev(10).getColor(x, y);
        h_1 += c1.getHueAngle();
        
    }
    
    h /= 100;
    h_1 /= 100;
    
    saturation.push_back(s);
    hues.push_back(h);
    bright.push_back(b);
    
    float absDist = abs(h_1 - h);
    
    dist.push_back(absDist);
    
    if(hues.size() > 100){
        hues.erase(hues.begin());
        dist.erase(dist.begin());
    }
    
    saveThermal(absDist);
}


void ThermalEngine::saveThermal(float absDist){
    
    ofxJSONElement response;
    response.open("http://localhost:3000/thermal.json?v=" + ofToString(absDist));
    
}

bool ThermalEngine::hasImages(){
    return images.size() > 0;
}

ofImage ThermalEngine::lastImage(){
    return images[images.size() - 1];
}

ofImage ThermalEngine::prev(int n){
    if (images.size() >= n)
        return images[images.size() - (n - 1)];
    return images[images.size() - 1];

}


