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
    
    
    
    images = vector<ofImage>();
    
    if(!BLACKMAGIC){
        vidGrabber.loadMovie("carlos.mov");
        vidGrabber.play();
    }
    
    
    for(int i = 0; i < 100; i ++)
        dist.push_back(0);
    
    target_x = 0.5;
    target_y = 0.5;
    delta_x = 0;
    delta_y = 0;
}

void ThermalEngine::updateThermal(ofImage blackMagicImg){
    
    if(BLACKMAGIC){
        img.cropFrom(blackMagicImg, delta_x,  delta_y, camWidth , camWidth * 450 / 910.);
    }
    else{
      vidGrabber.update();
        if(vidGrabber.isFrameNew()){
            img.setFromPixels(vidGrabber.getPixelsRef());
            img.crop( delta_x,  delta_y, camWidth , camWidth * 450 / 910. );
        }
    }


    images.push_back(img);
    
    if(images.size() > 2)
        calculateVariation();
    
    
    if(images.size() > BUFFER_SIZE)
        images.erase(images.begin());
}


void ThermalEngine::calculateVariation(){


    ofColor c = img.getColor(target_x, target_y);
    float h = c.getHueAngle();
    
    ofColor c1 = prev(1).getColor(target_x, target_y);
    float h_1 = c1.getHueAngle();

    float absDist = abs(h_1 - h);
    
    dist.push_back(absDist);
    
    if(dist.size() > 100){
        dist.erase(dist.begin());
    }
    
    calculateAvg();
    
    saveThermal(absDist);
}

void ThermalEngine::calculateAvg(){
    avg = 0;
    for(int i = 0; i <10; i++){
        avg += dist[dist.size() - i - 1];
    }
    avg /= 10;
    avg *= 100;
}

void ThermalEngine::saveThermal(float absDist){
    
    ofxJSONElement response;
    response.open("http://192.168.1.42:3000/thermal.json?v=" + ofToString(avg));
    
}

bool ThermalEngine::hasImages(){
    return images.size() > 0;
}

ofImage ThermalEngine::lastImage(){
    return images[images.size() - 1];
}

ofImage ThermalEngine::prev(int n){
    if (images.size() > n)
        return images[images.size() - (n + 1)];
    return images[images.size() - 1];

}


