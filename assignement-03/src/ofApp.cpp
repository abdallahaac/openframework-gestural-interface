#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
 
    // live stuff
    m_cam.initGrabber(Constants::VIDEO_WIDTH, Constants::VIDEO_HEIGHT);
    
    
    // add to gui
    m_cv_contourFinder.setMinAreaRadius(10);
    m_cv_contourFinder.setMaxAreaRadius(150);
    //    m_cv_contourFinder.setInvert(true); // find black instead of white
    
    m_colourImage.allocate(Constants::VIDEO_WIDTH, Constants::VIDEO_HEIGHT);

    
    // video stuff
    m_videoPlayer.load("tupperware.mov");    //Load the video file
    m_videoPlayer.play();
    m_videoPlayer.setLoopState(OF_LOOP_NORMAL);//Start the video to play
    m_gui.setup();
    
    
    // switching app states
    m_appMode = Constants::APP_MODE::FIND_DIFFERENCE;
    m_appModes.push_back("BACKGROUND_SUBTRACTION");    //from enum names in constants.h
    m_appModes.push_back("COLOR_TRACKING");
    
    //
    m_video_input = Constants::VIDEO_INPUT::VIDEO_ONE;

    
    
    m_threshold = 50;
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    
    
    // live cam
    m_cam.update();
    if(m_cam.isFrameNew() && isLive) {
        
        m_colourImage.setFromPixels(m_cam.getPixels());
        processLiveColour();
        
    }
    
    // video file
    m_videoPlayer.update();
    
    if(m_videoPlayer.isFrameNew() && isVideoOnePlaying &&!isLive  ){
        m_colourImage.setFromPixels(m_videoPlayer.getPixels());
    }
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    
    
    //if live video is selected
    
    if (isLive ){
        //
        
        //         drawing live camera with border
        
        if(m_appMode == Constants::APP_MODE::FIND_COLOR){
        
        ofTranslate(Constants::VIDEO_BORDER_SIZE, Constants::VIDEO_BORDER_SIZE);
            ofPushMatrix();
                ofFill();
                ofSetColor(0);
                ofDrawRectangle(0,0,Constants::VIDEO_WIDTH + Constants::VIDEO_BORDER_SIZE,Constants::VIDEO_HEIGHT + Constants::VIDEO_BORDER_SIZE);
            ofPopMatrix();
            ofSetColor(255);
            ofTranslate(Constants::VIDEO_BORDER_SIZE - 5, Constants::VIDEO_BORDER_SIZE - 5);
            m_colourImage.draw(0,0);
        

        // drawing live camera with border
        
        ofPushMatrix();
            
            
            // 10 : buffer
            ofTranslate(Constants::VIDEO_WIDTH + Constants::VIDEO_BORDER_SIZE * 2.0f, Constants::VIDEO_BORDER_SIZE-5);
            
            // video border
            ofPushMatrix();
                ofFill();
                ofSetColor(0);
                ofDrawRectangle(0,0,Constants::VIDEO_WIDTH /2+Constants::VIDEO_BORDER_SIZE,Constants::VIDEO_HEIGHT/2+Constants::VIDEO_BORDER_SIZE);
            ofPopMatrix();
            
            // scaling the camera
            ofScale(0.5f);
            ofSetColor(255);
            // drawing colour tracker camera
        m_colourImage.draw(Constants::VIDEO_BORDER_SIZE, Constants::VIDEO_BORDER_SIZE);
            m_cv_contourFinder.draw();
            
        ofPopMatrix();
        
        
        // relocate gui position
        ofPushMatrix();
        ofTranslate(-Constants::VIDEO_BORDER_SIZE,-Constants::VIDEO_BORDER_SIZE);
        // drawing gui to screen
        m_gui.draw();
        ofPopMatrix();
        
        // postion of eyedropper
        ofPushMatrix();
        ofTranslate(Constants::VIDEO_WIDTH + 5 * 2.0f, Constants::VIDEO_BORDER_SIZE * 25.0f);
        ofFill();
        ofSetColor(0);
        ofDrawRectangle(Constants::VIDEO_BORDER_SIZE,Constants::VIDEO_BORDER_SIZE,0,Constants::VIDEO_BORDER_BOX_WIDTH,Constants::VIDEO_BORDER_BOX_HEIGHT);
        ofSetColor(m_targetColor);
        ofDrawRectangle(Constants::VIDEO_BORDER_SIZE + 5,Constants::VIDEO_BORDER_SIZE + 5 ,0, Constants::VIDEO_BORDER_BOX_WIDTH-Constants::VIDEO_BORDER_SIZE, Constants::VIDEO_BORDER_BOX_HEIGHT-Constants::VIDEO_BORDER_SIZE);
        ofPopMatrix();
        
        
        m_gui.begin();
        {
            
            
            //backgroundColor is stored as an ImVec4 type but can handle ofColor
            ImGui::ColorEdit3("Selected Color", (float*)&m_trackedColor);
            
            //backgroundColor is stored as an ImVec4 type but can handle ofColor
            ImGui::SliderFloat("Threshold",&m_threshold,0,100);
            
            displayVideoOptionsInGui();
            displayVideoTrackingOptions();
            
        }
        
        m_gui.end();
            
        }else if (m_appMode == Constants::APP_MODE::FIND_DIFFERENCE){
            
            m_gui.begin();
            {
                
                
                //backgroundColor is stored as an ImVec4 type but can handle ofColor
                ImGui::ColorEdit3("Selected Color", (float*)&m_trackedColor);
                
                //backgroundColor is stored as an ImVec4 type but can handle ofColor
                ImGui::SliderFloat("Threshold",&m_threshold,0,100);
                
                displayVideoOptionsInGui();
                displayVideoTrackingOptions();
                
            }
            
            m_gui.end();
        }
        
    }else if( !isLive){
        

        if(m_appMode == Constants::APP_MODE::FIND_COLOR){
             
            
            ofTranslate(10, 10);
                ofPushMatrix();
                    ofFill();
                    ofSetColor(0);
                    ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                ofPopMatrix();
                ofSetColor(255);
                m_colourImage.draw(5,5);
            

            // drawing live camera with border

            ofPushMatrix();


                // 10 : buffer

            
            ofTranslate(m_colourImage.getWidth()+20, 0);


                // video border
                ofPushMatrix();
                    ofFill();
                    ofSetColor(0);
                    ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                ofPopMatrix();

                // scaling the camera
                ofSetColor(255);
                // drawing colour tracker camera
            ofPushMatrix();
            ofTranslate(5, 5);
                m_colourImage.draw(0,0);
                m_cv_contourFinder.draw();
            ofPopMatrix();

            ofPopMatrix();


            // relocate gui position
            ofPushMatrix();
           
            // drawing gui to screen
            m_gui.draw();
            ofPopMatrix();

            // postion of eyedropper
            ofPushMatrix();
            ofTranslate(Constants::VIDEO_WIDTH + 5 * 8.0f, -Constants::VIDEO_BORDER_SIZE  );
            ofFill();
            ofSetColor(0);
            ofDrawRectangle(Constants::VIDEO_BORDER_SIZE,Constants::VIDEO_BORDER_SIZE,0,Constants::VIDEO_BORDER_BOX_WIDTH,Constants::VIDEO_BORDER_BOX_HEIGHT);
            ofSetColor(m_targetColor);
            ofDrawRectangle(Constants::VIDEO_BORDER_SIZE + 5,Constants::VIDEO_BORDER_SIZE + 5 ,0, Constants::VIDEO_BORDER_BOX_WIDTH-Constants::VIDEO_BORDER_SIZE, Constants::VIDEO_BORDER_BOX_HEIGHT-Constants::VIDEO_BORDER_SIZE);
            ofPopMatrix();
            
            m_gui.begin();
            {
                displayVideoOptionsInGui();
                displayVideoTrackingOptions();

                m_gui.end();
            }
            
        }else if(m_appMode == Constants::APP_MODE::FIND_DIFFERENCE){
            
            
            ofTranslate(10, 10);
                ofPushMatrix();
                    ofFill();
                    ofSetColor(0);
                    ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                ofPopMatrix();
                ofSetColor(255);
                m_colourImage.draw(5,5);
            
            
            // vid 2
            ofPushMatrix();
            
                // 10 : buffer
            
                ofTranslate(m_colourImage.getWidth()+20, 0);

                    // video border
                    ofPushMatrix();
                        ofFill();
                        ofSetColor(0);
                        ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                    ofPopMatrix();

     
                    ofSetColor(255);
                    // drawing colour tracker camera
                    ofPushMatrix();
            
                        ofTranslate(5, 5);
                        m_graydiffImage.draw(0,0);
                       
            
                    ofPopMatrix();

            ofPopMatrix();

            
            //vid 3
            
            ofPushMatrix();
            
                // 10 : buffer
            
                ofTranslate(0, m_colourImage.getHeight() +20);

                    // video border
                    ofPushMatrix();
                        ofFill();
                        ofSetColor(0);
                        ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                    ofPopMatrix();

     
                    ofSetColor(255);
                    // drawing colour tracker camera
        
                    ofPushMatrix();
            
                        ofTranslate(5, 5);
                        m_grayMask.draw(0,0);
                        m_contourFinder.draw( 0,0 );
            
                    ofPopMatrix();

            ofPopMatrix();

            //vid 4
            
            ofPushMatrix();
            
                // 10 : buffer
            
                ofTranslate(m_colourImage.getWidth()+20, m_colourImage.getHeight() +20);

                    // video border
                    ofPushMatrix();
                        ofFill();
                        ofSetColor(0);
                        ofDrawRectangle(0,0,m_colourImage.getWidth()+10,m_colourImage.getHeight()+10);
                    ofPopMatrix();

     
                    ofSetColor(255);
                    // drawing colour tracker camera
                    ofPushMatrix();
            
                        ofTranslate(5, 5);
                        m_colourImage.draw(0,0);
               
    
                       
                    ofPopMatrix();

            ofPopMatrix();

            
            // drawing live camera with border
         
            
            ofSetLineWidth( 2 );
            
            ofPushMatrix();
                int w = m_colourImage.width ;
                int h = m_colourImage.height ;
                ofSetColor( 255);    //Set color for images drawing

            for (int i=0; i < m_trackingObject.size(); i++) {
                ofPoint p = m_trackingObject[i] + ofPoint( m_colourImage.width+10,  m_colourImage.height +10 );
                // draw cross on at the center of the blob
                ofLine( p.x - 20, p.y, p.x + 20, p.y );
                ofLine( p.x, p.y - 20, p.x, p.y + 20 );
            }
        
                ofSetLineWidth( 1 );
            ofPopMatrix();
     
            
            
            
            m_gui.begin();
            {
                displayVideoOptionsInGui();
                displayVideoTrackingOptions();

                m_gui.end();
            }
            
        }
        
        
    }
}


//}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    if(key=='1'){
//        cout << "pressed";
//        isLive != isLive;
//
//
//    }else{
//
//        isVideoOnePlaying != isVideoOnePlaying;
//    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
    ofPushMatrix();
    
    //need to convert from screen-space coordinates to "video-based" coordinates so we don't click and set an invalid pixel coordinate when outside image
    ofRectangle videoRect = ofRectangle(0 ,0 ,Constants::VIDEO_WIDTH,Constants::VIDEO_HEIGHT);
    
    
    //step 1 - clamp
    int convertScreenToImageSpace_X = ofClamp(x, videoRect.getMinX(), videoRect.getMaxX());
    int convertScreenToImageSpace_Y = ofClamp(y, videoRect.getMinY(), videoRect.getMaxY());
    
    //shift to image-space (zero at top-left corner)
    
    
    convertScreenToImageSpace_X -= videoRect.getMinX();
    convertScreenToImageSpace_Y -= videoRect.getMinY();
    
    
    //now find that pixel
    const int index = (convertScreenToImageSpace_X + convertScreenToImageSpace_Y * m_colourImage.getWidth()) * m_colourImage.getPixels().getBytesPerPixel();
    
    m_trackedColor[0] = m_colourImage.getPixels()[index + 0] / 255.0f;
    m_trackedColor[1] = m_colourImage.getPixels()[index + 1] / 255.0f ;
    m_trackedColor[2]= m_colourImage.getPixels()[index + 2] / 255.0f;
    
    
    cout <<"r: " << m_targetColor[0] << endl;
    cout << "g: "<< m_trackedColor[1] << endl;
    cout << "b: " <<m_trackedColor[2]  << endl;
    
    m_targetColor.r = m_trackedColor[0]*255.0f;
    m_targetColor.g = m_trackedColor[1]*255.0f;
    m_targetColor.b = m_trackedColor[2]*255.0f;
    
    ofPopMatrix();
    
    
}

void ofApp::processLiveColour(){
    
    m_cv_contourFinder.setTargetColor(m_targetColor, true ? ofxCv::TRACK_COLOR_HS : ofxCv::TRACK_COLOR_RGB);
    m_cv_contourFinder.setThreshold(m_threshold);
    m_cv_contourFinder.findContours(m_cam);
    
    
}
void ofApp::processVideoColour(){
    
    
    m_cv_contourFinder.setTargetColor(m_targetColor, true ? ofxCv::TRACK_COLOR_HS : ofxCv::TRACK_COLOR_RGB);
    m_cv_contourFinder.setThreshold(m_threshold);
    m_cv_contourFinder.findContours(m_colourImage);
    
    
}
void ofApp::processLiveSegmentation(){
    
    
    
}
void ofApp::processVideoSegmentation(){
    


            if ( !m_detectionImage.bAllocated ) {
                m_detectionImage.allocate( m_colourImage.width * 0.5,
                                          m_colourImage.height * 0.5 );
            }
            m_detectionImage.scaleIntoMe( m_colourImage, CV_INTER_NN );

            //Convert to grayscale image
            m_grayImage = m_detectionImage;

            //Smoothing image
            m_grayBlurredImage = m_grayImage;
            m_grayBlurredImage.blurGaussian( 9 );

            //Store first frame to background image
            if ( !m_grayMask.bAllocated ) {
                m_grayBackgroundImage = m_grayBlurredImage;
            }

            //Find difference of the frame and background
            m_graydiffImage.absDiff(m_grayImage, m_grayBackgroundImage);

            //Thresholding for obtaining binary image
            m_grayMask = m_graydiffImage;
            m_grayMask.threshold( 40 );
            m_grayMask.invert();
            //Here value 40 is the threshold parameter.
            //It should be adjusted for good results when using another videos than in example.

            //Find contours
            m_contourFinder.findContours( m_grayMask, 10, 10000, 20, false );

            //Store objects' centers
            vector<ofxCvBlob>  &blobs = m_contourFinder.blobs;
            int n = blobs.size();    //Get number of blobs
            m_trackingObject.resize( n );        //Resize obj array
            for (int i=0; i<n; i++) {
                m_trackingObject[i] = blobs[i].centroid;    //Fill obj array
            }


    
    
}





// UI
void ofApp::displayVideoOptionsInGui(){
    
    
    if(ImGui::CollapsingHeader("PLEASE SELECT VIDEO INPUT")){
        if(ImGui::Button("LIVE CAMERA")){
            
            m_video_input = Constants::VIDEO_INPUT::LIVE_CAM;
        }
        if(ImGui::Button("TUPPERWARE")){
            m_video_input = Constants::VIDEO_INPUT::VIDEO_ONE;
            
        }
        if(ImGui::Button("FRUITS")){
            
            m_video_input = Constants::VIDEO_INPUT::VIDEO_TWO;
        }
        
              }
        switch (m_video_input) {
            case Constants::VIDEO_INPUT::LIVE_CAM:
            {
                isLive = true;
                isVideoOnePlaying = false;
          
         
                break;
            }
            case Constants::VIDEO_INPUT::VIDEO_ONE:
            {
                isVideoOnePlaying= true;
                isLive = false;
                
                break;
            }
                
        }
    
}

void ofApp::displayVideoTrackingOptions(){
    
        
        static int currentListBoxIndex = 0;
        if (ofxImGui::VectorCombo("APP MODE", &currentListBoxIndex, m_appModes)) {
            std::cout << "SELECTED APP MODE: " + m_appModes[currentListBoxIndex] << std::endl;
            m_appMode = (Constants::APP_MODE)currentListBoxIndex;
        }
        switch (m_appMode) {
        case Constants::APP_MODE::FIND_DIFFERENCE:
        {
         
            processVideoSegmentation();
            
            break;
        }
        case Constants::APP_MODE::FIND_COLOR:
        {
            processVideoColour();
            break;
        }
    }
}


