//
//  DeltaObject.h
//  LeapGestures
//
//  Created by Emilio Espinosa on 6/30/17.
//
//

#ifndef DeltaObject_h
#define DeltaObject_h

#include <stdio.h>
#include "Leap.h"

namespace DeltaGest { 
    
    class DeltaObject {
        
    protected:
        Leap::Vector _absolutePos;
        Leap::Vector _relativePos;
        Leap::Vector _orientation;
                
    public:
        virtual Leap::Vector getAbsolutePos() { return _absolutePos; }
        virtual Leap::Vector getRelativePos() { return _relativePos; }
        virtual Leap::Vector getOrientation() { return _orientation; }
        
    };
    
}

#endif /* DeltaObject_h */
