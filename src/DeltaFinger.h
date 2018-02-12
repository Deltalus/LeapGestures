//
//  DeltaFinger.h
//  LeapGestures
//
//  Created by Emilio Espinosa on 6/30/17.
//
//

#ifndef DeltaFinger_h
#define DeltaFinger_h

#include <stdio.h>
#include "DeltaObject.h"

namespace DeltaGest {
    
    class DeltaFinger: public DeltaObject {
        
        bool isExtended = false;
        
    public:
        
        void update(Leap::Finger);
    };
    
}

#endif /* DeltaFinger_h */
