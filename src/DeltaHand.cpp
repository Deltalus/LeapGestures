//
//  DeltaHand.cpp
//  LeapGestures
//
//  Created by Emilio Espinosa on 6/30/17.
//
//

#include "DeltaHand.h"

using namespace DeltaGest;

void DeltaHand::update(Leap::Hand hand) {
    
    _relativePos = hand.stabilizedPalmPosition() - _absolutePos;
    _absolutePos = hand.stabilizedPalmPosition();
    _orientation = hand.direction();
    // TODO: make sure the roll is properly calculated
    
    for (int i = 0; i < 5; i++) {
        fingers[i].update(hand.finger(hand.id() * 10 + i));
    }
    
}

GRT::VectorDouble DeltaHand::absTimeSeriesData() {
    
    GRT::VectorDouble timeSeries(36);
    timeSeries[0] = _absolutePos.x;
    timeSeries[1] = _absolutePos.y;
    timeSeries[2] = _absolutePos.z;
    timeSeries[3] = _orientation.pitch();
    timeSeries[4] = _orientation.yaw();
    timeSeries[5] = _orientation.roll();
    
    for (int i = 0; i < 5; i++) {
        timeSeries[6 * (i + 1)] = fingers[i].getAbsolutePos().x;
        timeSeries[6 * (i + 1) + 1] = fingers[i].getAbsolutePos().y;
        timeSeries[6 * (i + 1) + 2] = fingers[i].getAbsolutePos().z;
        timeSeries[6 * (i + 1) + 3] = fingers[i].getOrientation().pitch();
        timeSeries[6 * (i + 1) + 4] = fingers[i].getOrientation().yaw();
        timeSeries[6 * (i + 1) + 5] = fingers[i].getOrientation().roll();
    }
    
    return timeSeries;
}

GRT::VectorDouble DeltaHand::relTimeSeriesData() {
    
    GRT::VectorDouble timeSeries(36);
    timeSeries[0] = _relativePos.x;
    timeSeries[1] = _relativePos.y;
    timeSeries[2] = _relativePos.z;
    timeSeries[3] = _orientation.pitch();
    timeSeries[4] = _orientation.yaw();
    timeSeries[5] = _orientation.roll();
    
    for (int i = 0; i < 5; i++) {
        timeSeries[6 * (i + 1)] = fingers[i].getRelativePos().x;
        timeSeries[6 * (i + 1) + 1] = fingers[i].getRelativePos().y;
        timeSeries[6 * (i + 1) + 2] = fingers[i].getRelativePos().z;
        timeSeries[6 * (i + 1) + 3] = fingers[i].getOrientation().pitch();
        timeSeries[6 * (i + 1) + 4] = fingers[i].getOrientation().yaw();
        timeSeries[6 * (i + 1) + 5] = fingers[i].getOrientation().roll();
    }
    
    return timeSeries;
}
