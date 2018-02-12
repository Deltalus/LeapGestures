//
//  DeltaFinger.cpp
//  LeapGestures
//
//  Created by Emilio Espinosa on 6/30/17.
//
//

#include "DeltaFinger.h"

using namespace DeltaGest;

void DeltaFinger::update(Leap::Finger finger) {
    
    isExtended = finger.isExtended();
    
    _relativePos = finger.stabilizedTipPosition() - _absolutePos;
    _absolutePos = finger.stabilizedTipPosition();
    _orientation = finger.direction();
    
}
