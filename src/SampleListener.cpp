//
//  SampleListener.cpp
//  LeapGestures
//
//  Created by Emilio Espinosa on 4/9/17.
//
//

#include "SampleListener.h"
#include "ofApp.h"

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();
    
    Leap::HandList handList = frame.hands();
    Leap::HandList::const_iterator iter;
    
    for(iter = handList.begin(); iter != handList.end(); iter++) {
        Hand currentHand = *iter;
        
        application->recieveLeapData(currentHand);
    }
    
}
