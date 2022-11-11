#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxImGui.h"
#include "Constants.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);

    
    
    void storeTrackedObjectCenters();
    
    // display functions
    void displayVideoOptionsInGui();
    void displayVideoTrackingOptions();
    void displayLiveVideoTrackingOptions();
    void displayBufferingOptions();
    
    // processing functions
    void processVideoSegmentation(); // segmentation
    void processVideoColour();
    
    void processBuffering();
    void processLiveColour();
    void processLiveSegmentation();
    
    
    bool                                isLive,isVideoOnePlaying;
    
    
    
    
    // live camera variables
    
    ofVideoGrabber                        m_cam  ;
     ofVideoPlayer                         m_videoPlayer;
    
    ofxCv::ContourFinder                  m_cv_contourFinder, m_cv_live_contourFinder;
    ofColor                               m_targetColor;
    GLfloat                               borderSize = 20.0f;
    float                                 m_trackedColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    
    
    //app states variables
    //to be renamed
    Constants::APP_MODE                   m_appMode;
    std::vector<std::string>              m_appModes;
    Constants::VIDEO_INPUT                m_video_input;
    
    
    
    
    
    
    //    ofxImGui::Gui   m_gui;
    ofxImGui::Gui                        m_gui;
    float                                m_threshold;
    ofParameter<bool>                    trackingColour;
    
    
    // for tracking
    vector<ofPoint>                      m_trackingObject;                //object's centers
    
    // for segmentation
    ofxCvColorImage                       m_colourImage, m_detectionImage;
    ofxCvGrayscaleImage                   m_grayImage, m_grayBlurredImage, m_grayBackgroundImage, m_graydiffImage, m_grayMask;
    ofxCvContourFinder                    m_contourFinder;
    
    
};
