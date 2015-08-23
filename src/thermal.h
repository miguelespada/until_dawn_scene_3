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
#include "thermalEngine.h"


class Thermal: public State
{
    
    Assets *assets;
    
public:
    Thermal(App *g);
    ~Thermal(){};
    std::string toString() { return "Thermal"; }
    void update();
    void draw();
    void next();
    
    void drawTexts();
    void drawElapsedTime();
    void drawThermalData();
    void drawTarget();
    
    void drawThermalVariation();
    void drawTemperature();
    float initial_time;
    
    float temperature;
    
    ThermalEngine *thermalEngine;
};


#endif /* defined(__until_dawn_screen_3__termal__) */

