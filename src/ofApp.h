#pragma once

#include "ofMain.h"

#include "Leap.h"
#include "GRT.h"
#include "SampleListener.h"
#include "DeltaHand.h"

using namespace GRT;
using namespace Leap;

enum Selection {
     Right, Left, Both
};

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    void recieveLeapData(Hand hand);

    Controller controller;
    SampleListener listener;
    
    DeltaGest::DeltaHand rightHand;
    DeltaGest::DeltaHand leftHand;
    
    Selection trainingSelection;
    
    //Create some variables for the demo
    TimeSeriesClassificationData trainingDataRight;      //This will store our training data
    MatrixDouble timeseriesRight;                        //This will store a single training sample
    GestureRecognitionPipeline pipelineRight;            //This is a wrapper for our classifier and any pre/post processing modules
    UINT trainingClassLabelRight;                        //This will hold the current label for when we are training the classifier
    float predictionRight;
    
    TimeSeriesClassificationData trainingDataLeft;      //This will store our training data
    MatrixDouble timeseriesLeft;                        //This will store a single training sample
    GestureRecognitionPipeline pipelineLeft;            //This is a wrapper for our classifier and any pre/post processing modules
    UINT trainingClassLabelLeft;                        //This will hold the current label for when we are training the classifier
    float predictionLeft;
    
    TimeSeriesClassificationData trainingDataBoth;      //This will store our training data
    MatrixDouble timeseriesBoth;                        //This will store a single training sample
    GestureRecognitionPipeline pipelineBoth;            //This is a wrapper for our classifier and any pre/post processing modules
    UINT trainingClassLabelBoth;                        //This will hold the current label for when we are training the classifier
    float predictionBoth;
    
    bool record;                                    //This is a flag that keeps track of when we should record training data
    string infoText;                                //This string will be used to draw some info messages to the main app window
    
};
