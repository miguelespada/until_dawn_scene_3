//
//  State.cpp
//  until_dawn_screen_3
//
//  Created by miguel on 24/08/15.
//
//

#include "State.h"
#include "App.h"
#include "standby.h"
#include "calculandoIndex.h"
#include "index.h"

void State::standby(){
    app->setCurrentState(new Standby(app));
    delete this;

}
void State::index(){
    app->setCurrentState(new Index(app));
    delete this;
}

void State::calculandoIndex(){
    app->setCurrentState(new class calculandoIndex(app));
    delete this;
}