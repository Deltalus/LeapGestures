#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    listener.application = this;
    controller.addListener(listener);
    ofSetFrameRate(60);
    
    //Initialize the training and info variables
    infoText = "";
    trainingClassLabelRight = 1;
    trainingClassLabelLeft = 1;
    trainingClassLabelBoth = 1;
    record = false;
    
    //The input to the training data will be the [x y] from the mouse, so we set the number of dimensions to 2
    trainingDataRight.setNumDimensions( 36 );
    trainingDataLeft.setNumDimensions( 36 );
    trainingDataBoth.setNumDimensions( 72 );
    
    //Initialize the DTW classifier
    DTW dtw;
    
    //Turn on null rejection, this lets the classifier output the predicted class label of 0 when the likelihood of a gesture is low
    dtw.enableNullRejection( true );
    
    //Set the null rejection coefficient to 3, this controls the thresholds for the automatic null rejection
    //You can increase this value if you find that your real-time gestures are not being recognized
    //If you are getting too many false positives then you should decrease this value
    dtw.setNullRejectionCoeff( 1 );
    
    //Turn on the automatic data triming, this will remove any sections of none movement from the start and end of the training samples
    dtw.enableTrimTrainingData(true, 0.1, 90);
    
    //Offset the timeseries data by the first sample, this makes your gestures (more) invariant to the location the gesture is performed
    dtw.setOffsetTimeseriesUsingFirstSample(true);
    
    //Add the classifier to the pipeline (after we do this, we don't need the DTW classifier anymore)
    pipelineRight.setClassifier( dtw );
    pipelineLeft.setClassifier( dtw );
    pipelineBoth.setClassifier( dtw );
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //If we are recording training data, then add the current sample to the training data set
    if( record ){
        // TODO: switch case this event to add sample only to the correct time series data
        //timeseriesRight.push_back( sample );
        //timeseriesLeft.push_back( sample );
        //timeseriesBoth.push_back( sample );
        VectorDouble sample;
        switch (trainingSelection) {
            case Right:
                sample = rightHand.absTimeSeriesData();
                timeseriesRight.push_back(sample);
                break;
            case Left:
                sample = leftHand.absTimeSeriesData();
                timeseriesLeft.push_back(sample);
                break;
            case Both:
                VectorDouble right = rightHand.absTimeSeriesData();
                VectorDouble left = leftHand.absTimeSeriesData();
                sample.insert(sample.end(), right.begin(), right.end());
                sample.insert(sample.end(), left.begin(), left.end());
                timeseriesBoth.push_back(sample);
                break;
                
        }
    }
    
    //If the pipeline has been trained, then run the prediction
    
    VectorDouble right = rightHand.absTimeSeriesData();
    VectorDouble left = leftHand.absTimeSeriesData();
    
    if( pipelineRight.getTrained() ){
        pipelineRight.predict( right );
        predictionRight = pipelineRight.getMaximumLikelihood();
        VectorDouble likelihoods = pipelineRight.getClassLikelihoods();
    }
    
    if (pipelineLeft.getTrained()) {
        pipelineLeft.predict( left );
        predictionLeft = pipelineLeft.getMaximumLikelihood();
    }
    
    if (pipelineBoth.getTrained()) {
        VectorDouble sample;
        sample.insert(sample.end(), right.begin(), right.end());
        sample.insert(sample.end(), left.begin(), left.end());
        pipelineBoth.predict( sample );
        predictionBoth = pipelineBoth.getMaximumLikelihood();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    string text;
    int textX = 20;
    int textY = 20;
    
    //Draw the training info
    ofSetColor(255, 255, 255);
    text = "------------------- TrainingInfo -------------------";
    ofDrawBitmapString(text, textX,textY);
    
    if( record ) ofSetColor(255, 0, 0);
    else ofSetColor(255, 255, 255);
    textY += 15;
    text = record ? "RECORDING" : "Not Recording";
    ofDrawBitmapString(text, textX,textY);
    
    ofSetColor(255, 255, 255);
    textY += 15;
    text = "TrainingClassLabelRight: " + ofToString(trainingClassLabelRight);
    ofDrawBitmapString(text, textX,textY);
    
    text = "TrainingClassLabelLeft: " + ofToString(trainingClassLabelLeft);
    ofDrawBitmapString(text, textX + 250, textY);
    
    text = "TrainingClassLabelBoth: " + ofToString(trainingClassLabelBoth);
    ofDrawBitmapString(text, textX + 500, textY);
    
    textY += 15;
    text = "NumTrainingSamplesRight: " + ofToString(trainingDataRight.getNumSamples());
    ofDrawBitmapString(text, textX,textY);
    
    text = "NumTrainingSamplesLeft: " + ofToString(trainingDataLeft.getNumSamples());
    ofDrawBitmapString(text, textX + 250,textY);
    
    text = "NumTrainingSamplesBoth: " + ofToString(trainingDataBoth.getNumSamples());
    ofDrawBitmapString(text, textX + 500,textY);
    
    textY += 30;
    text = "--------------------- Selection ---------------------";
    ofDrawBitmapString(text, textX,textY);
    
    textY += 15;
    switch (trainingSelection) {
        case Right:
            text = "Right";
            break;
        case Left:
            text = "Left";
            break;
        case Both:
            text = "Both";
            break;
    }
    ofDrawBitmapString(text, textX, textY);
    
    //Draw the prediction info
    textY += 30;
    text = "------------------- Prediction Info -------------------";
    ofDrawBitmapString(text, textX, textY);
    
    textY += 15;
    text =  pipelineRight.getTrained() ? "Model Trained: YES" : "Model Trained: NO";
    ofDrawBitmapString(text, textX,textY);
    
    text =  pipelineLeft.getTrained() ? "Model Trained: YES" : "Model Trained: NO";
    ofDrawBitmapString(text, textX + 250, textY);
    
    text =  pipelineBoth.getTrained() ? "Model Trained: YES" : "Model Trained: NO";
    ofDrawBitmapString(text, textX + 500, textY);
    
    textY += 15;
    text = "PredictedClassLabel: " + ofToString(pipelineRight.getPredictedClassLabel());
    ofDrawBitmapString(text, textX,textY);
    
    text = "PredictedClassLabel: " + ofToString(pipelineLeft.getPredictedClassLabel());
    ofDrawBitmapString(text, textX + 250,textY);
    
    text = "PredictedClassLabel: " + ofToString(pipelineBoth.getPredictedClassLabel());
    ofDrawBitmapString(text, textX + 500,textY);
    
    textY += 15;
    text = "Likelihood: " + ofToString(pipelineRight.getMaximumLikelihood());
    ofDrawBitmapString(text, textX,textY);
    
    text = "Likelihood: " + ofToString(pipelineLeft.getMaximumLikelihood());
    ofDrawBitmapString(text, textX + 250,textY);
    
    text = "Likelihood: " + ofToString(pipelineBoth.getMaximumLikelihood());
    ofDrawBitmapString(text, textX + 500,textY);
    
    textY += 15;
    text = "SampleRate: " + ofToString(ofGetFrameRate(),2);
    ofDrawBitmapString(text, textX,textY);
    
    
    //Draw the info text
    textY += 30;
    text = "InfoText: " + infoText;
    ofDrawBitmapString(text, textX,textY);
    
    //Draw the timeseries data
//    if( record ){
//        ofFill();
//        for(UINT i=0; i<timeseriesRight.getNumRows(); i++){
//            double x = timeseriesRight[i][0];
//            double y = timeseriesRight[i][1];
//            double r = ofMap(i,0,timeseriesRight.getNumRows(),0,255);
//            double g = 0;
//            double b = 255-r;
//            
//            ofSetColor(r,g,b);
//            ofDrawEllipse(x,y,5,5);
//        }
//    }
//    
//    if( pipelineRight.getTrained() ){
//        
//        //Draw the data in the DTW input buffer
//        DTW *dtw = pipelineRight.getClassifier< DTW >();
//        
//        if( dtw != NULL ){
//            vector< VectorDouble > inputData = dtw->getInputDataBuffer();
//            for(UINT i=0; i<inputData.size(); i++){
//                double x = inputData[i][0];
//                double y = inputData[i][1];
//                double r = ofMap(i,0,inputData.size(),0,255);
//                double g = 0;
//                double b = 255-r;
//                
//                ofSetColor(r,g,b);
//                ofDrawEllipse(x,y,5,5);
//            }
//        }
//    }

}

//--------------------------------------------------------------
// Press 'r' to begin/stop recording training data
// Press '[' to go to next selection label (gesture label)
// Press ']' to go to previous selection label (gesture label)
// Press 't' to train the pipeline
// Press 's' to save the training data
// Press 'l' to load training data
// Press 'c' to clear training data
// Press '1' to train gesture of only right hand
// Press '2' to train gesture of only left hand
// Press '3' to train gesture of both hands

void ofApp::keyPressed(int key){
    infoText = "";
    TimeSeriesClassificationData* trainingData;
    MatrixDouble* timeseries;
    GestureRecognitionPipeline* pipeline;
    
    switch (trainingSelection) {
        case Right:
            trainingData = &trainingDataRight;
            timeseries = &timeseriesRight;
            pipeline = &pipelineRight;
            break;
        case Left:
            trainingData = &trainingDataLeft;
            timeseries = &timeseriesLeft;
            pipeline = &pipelineLeft;
            break;
        case Both:
            trainingData = &trainingDataBoth;
            timeseries = &timeseriesBoth;
            pipeline = &pipelineBoth;
            break;
    }
    
    switch ( key) {
        case 'r':
            record = !record;
            if( !record ){
                switch (trainingSelection) {
                    case Right:
                        trainingData->addSample(trainingClassLabelRight, *timeseries);
                        break;
                    case Left:
                        trainingData->addSample(trainingClassLabelLeft, *timeseries);
                        break;
                    case Both:
                        trainingData->addSample(trainingClassLabelBoth, *timeseries);
                        break;
                }
                timeseries->clear();
            }
            break;
        case '[':
            switch (trainingSelection) {
                case Right:
                    if( trainingClassLabelRight > 1 )
                        trainingClassLabelRight--;
                    break;
                case Left:
                    if( trainingClassLabelLeft > 1 )
                        trainingClassLabelLeft--;
                    break;
                case Both:
                    if( trainingClassLabelBoth > 1 )
                        trainingClassLabelBoth--;
                    break;
            }
            break;
        case ']':
            switch (trainingSelection) {
                case Right:
                    trainingClassLabelRight++;
                    break;
                case Left:
                    trainingClassLabelLeft++;
                    break;
                case Both:
                    trainingClassLabelBoth++;
                    break;
            }
            break;
        case 't':
            if (pipeline->train(*trainingData)) {
                infoText = "Right Pipeline Trained";
            }else infoText = "WARNING: Failed to train pipeline";
            break;
        case 's':
            if( trainingData->saveDatasetToFile("/Users/Emilio/Documents/TestData.txt") ){
                infoText = "Training data saved to file";
            }else infoText = "WARNING: Failed to save training data to file";
            break;
        case 'l':
            if( trainingData->loadDatasetFromFile("TestData.txt") ){
                infoText = "Training data saved to file";
            }else infoText = "WARNING: Failed to load training data from file";
            break;
        case 'c':
            trainingData->clear();
            infoText = "Training data cleared";
            break;
        case '1':
            trainingSelection = Right;
            break;
        case '2':
            trainingSelection = Left;
            break;
        case '3':
            trainingSelection = Both;
            break;
        default:
            break;
    }
}

void ofApp::recieveLeapData(Hand hand) {
    int appWidth = 1024;
    int appHeight = 768;
    
    InteractionBox iBox = controller.frame().interactionBox();
    Pointable pointable = controller.frame().pointables().frontmost();
    Leap::Vector leapPoint = hand.stabilizedPalmPosition();
    
    Leap::Vector normalizedPoint = iBox.normalizePoint(leapPoint, false);
    
    int appX = normalizedPoint.x * appWidth;
    int appY = (1 - normalizedPoint.y) * appHeight;
    //palmPosition[0] = appX;
    //palmPosition[1] = appY;
    
    if (hand.isRight())
        rightHand.update(hand);
    if (hand.isLeft())
        leftHand.update(hand);
}
