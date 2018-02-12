//
//  SampleListener.hpp
//  LeapGestures
//
//  Created by Emilio Espinosa on 4/9/17.
//
//

#ifndef SampleListener_h
#define SampleListener_h

#include <stdio.h>
#include "Leap.h"

using namespace Leap;

class ofApp;

class SampleListener : public Listener {
public:
    
    ofApp* application;
        
    void onConnect(const Controller&);
    void onFrame(const Controller&);
};

#endif /* SampleListener_h */
