#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    duration = 60;
    ofResetElapsedTimeCounter();
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // red EB4A50
    // yellow F9CD4A
    // green 4FAD9F
    // blue 20629D
    // tan F1ECE5
}

//--------------------------------------------------------------
void ofApp::update(){
    timerPosition = duration - (float(ofGetElapsedTimeMillis()) / 1000);
    angle = -90 - (timerPosition / duration) * 360;
    center = ofPoint(3 * (ofGetWindowWidth() / 4), ofGetWindowHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPath circle;
    circle.arc(center, 300, 300, 0, 360);
    circle.arcNegative(center, 200, 200, 0, 360);
    circle.close();
    circle.setCircleResolution(600);
    // ofColor background(50, 50, 50);
    // circle.setFillColor(background);
    circle.setFillHexColor(0xF1ECE5);
    circle.setFilled(true);
    circle.draw();
    
    ofPath segment;
    segment.arc(center, 300, 300, angle, -90);
    segment.arcNegative(center, 200, 200, -90, angle);
    segment.close();
    segment.setCircleResolution(600);
    ofColor c(255, 0,0);
    //segment.setFillColor(c);
    segment.setFillHexColor(0xEB4A50);
    segment.setFilled(true);
    segment.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
