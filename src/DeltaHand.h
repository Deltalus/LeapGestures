//
//  DeltaHand.h
//  LeapGestures
//
//  Created by Emilio Espinosa on 6/30/17.
//
//

#ifndef DeltaHand_h
#define DeltaHand_h

#include <stdio.h>
#include "DeltaFinger.h"
#include "GRT.h"

namespace DeltaGest {
    
    class DeltaHand: public DeltaObject {
        
        bool visible;
        DeltaFinger fingers[5];
        
    public:
        void update(Leap::Hand);
        GRT::VectorDouble absTimeSeriesData();
        GRT::VectorDouble relTimeSeriesData();
    };
}



#endif /* DeltaHand_h */
