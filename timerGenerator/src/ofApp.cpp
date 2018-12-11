#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // red EB4A50
    // yellow F9CD4A
    // green 4FAD9F
    // blue 20629D
    // tan F1ECE5
    
    ofSetFrameRate(60);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofTrueTypeFont::setGlobalDpi(72);
    futuraBold.load("Futura-Bold-03.ttf", 120, true, true);
    
    reset();
    
}

void ofApp::reset() {
    if (isRunning) {
        startStop();
    }
    isPaused = false;
    timerAtPause = 0;
    duration = 420;
    
}

void ofApp::startStop() {
    if (isRunning) {
        isRunning = false;
        isPaused = true;
        timerAtPause = timerAtPause + float(ofGetElapsedTimeMillis()) / 1000;
    } else {
        if (isPaused) {
            isPaused = false;
        }
        ofResetElapsedTimeCounter();
        isRunning = true;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (isRunning) {
        timerPosition = duration - (float(ofGetElapsedTimeMillis()) / 1000) - timerAtPause;
    } else {
        timerPosition = duration - timerAtPause;
    }
    angle = -90 - (timerPosition / duration) * 360;
    center = ofPoint(3 * (ofGetWindowWidth() / 4), ofGetWindowHeight() / 2);
    int minutes = int(timerPosition / 60);
    int seconds = timerPosition - minutes*60;
    displayValue = ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
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
    
    
    
    ofSetHexColor(0xffffff);
    ofRectangle bounds = futuraBold.getStringBoundingBox("00:00", 0, 0);
    futuraBold.drawString(displayValue, center.x - bounds.width/2, center.y + bounds.height/2);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            reset();
            break;
        case ' ':
            startStop();
            break;
        case OF_KEY_UP:
            duration += 60;
            break;
        case OF_KEY_DOWN:
            if (duration >= 120) {
                duration -= 60;
            }
        default:
            break;
    }
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
