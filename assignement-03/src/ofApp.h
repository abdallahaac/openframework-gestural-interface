#pragma once

#include "ofMain.h"
#include "App_Constants.h"
#include "ofxImGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void dragEvent(ofDragInfo dragInfo);
    
    
        
        ofxImGui::Gui                       m_gui;  //gui
        
        App_Constants::APP_MODE             m_appMode; // different app modes .i.e. Background subtraction, colour tracking + any additional filters
    
        
    

		
};
