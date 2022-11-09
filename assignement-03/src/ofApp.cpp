#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //setting background color
    ofBackground(255);
    
    //setting up gui
    m_gui.setup();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    

    
    //drawing gui to canvas
    m_gui.begin();
    {
        if (ImGui::Button("Hi")) {
            cout<< "worked";
        }
        
    }
    m_gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
