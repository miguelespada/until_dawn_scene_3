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
    camHeight 		= 316;
    
    
    
    images = vector<ofImage>();
    
    for(int i = 0; i < 100; i ++)
        dist.push_back(0);
    
    target_x = 0.5;
    target_y = 0.5;
    delta_x = 0;
    delta_y = 0;
    
    sender.setup("192.168.1.42", 12350);
}

void ThermalEngine::updateThermal(ofImage heatImg){

    images.push_back(heatImg);
    
    if(images.size() > 2)
        calculateVariation();
    
    
    if(images.size() > BUFFER_SIZE)
        images.erase(images.begin());
}


void ThermalEngine::calculateVariation(){

    ofColor c = prev(1).getColor(target_x  * camWidth , target_y * camHeight);
    int h = c.getHue();
    
    ofColor c1 = prev(2).getColor(target_x  * camWidth , target_y * camHeight);
    int h_1 = c1.getHue();

    
    int absDist = abs(h_1 - h);
    
    absDist = ofClamp(absDist, 0, 1);
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
}

void ThermalEngine::saveThermal(float absDist){
    
    
    ofxOscMessage m;
    m.setAddress("/flow");
    m.addFloatArg(avg);
    sender.sendMessage(m);
    
    
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


