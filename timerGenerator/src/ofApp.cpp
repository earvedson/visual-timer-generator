#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // red EB4A50
    // yellow F9CD4A
    // green 4FAD9F
    // blue 20629D
    // tan F1ECE5
    
    timerWidth = 1920/2;
    timerHeight = 1080/2;
    
    ofSetFrameRate(60);
    
    ofSetLogLevel(OF_LOG_ERROR);
    
    ofTrueTypeFont::setGlobalDpi(72);
    futuraBold.load("Futura-Bold-03.ttf", 120, true, true);
    
    reset();
    
    // video
    sampleRate = 44100;
    channels = 2;
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    vidRecorder.setFfmpegLocation(ofFilePath::getAbsolutePath("ffmpeg"));
    
    fileName = "testMovie";
    fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    
//    vidRecorder.setVideoCodec("mpeg4");
//    vidRecorder.setVideoBitrate("800k");
//    vidRecorder.setAudioCodec("mp3");
//    vidRecorder.setAudioBitrate("192k");
    
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    
    //    soundStream.listDevices();
    //    soundStream.setDeviceID(11);
    // soundStream.setup(this, 0, channels, sampleRate, 256, 4);
    
    // from audioOutputExample
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = channels;
    settings.numInputChannels = 0;
    settings.bufferSize = 256;
    soundStream.setup(settings);
    
    // above needs to be looked at more closely
    
    ofSetWindowShape(1920/2, 1080/2);
    bRecording = false;
    ofEnableAlphaBlending();
    
//    if(!vidRecorder.isInitialized())
//    {
//        vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 1920, 1080, 30); // no audio
//    }
//
//    rgbFbo.allocate(1920, 1080, GL_RGB);
    
}

void ofApp::reset() {
    if (isRunning) {
        startStop();
    }
    isPaused = false;
    timerAtPause = 0;
    duration = 60;
    
}

void ofApp::startStop() {
    if (isRunning) {
        isRunning = false;
        isPaused = true;
        timerAtPause = timerAtPause + float(ofGetElapsedTimeMillis()) / 1000;
//        vidRecorder.setPaused(true);
    } else {
        if (isPaused) {
            isPaused = false;
//            vidRecorder.setPaused(false);
        }
        ofResetElapsedTimeCounter();
        isRunning = true;
//        vidRecorder.start();
    }
}

void ofApp::exit(){
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    vidRecorder.close();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (isRunning) {
        timerPosition = duration - (float(ofGetElapsedTimeMillis()) / 1000) - timerAtPause;
    } else {
        timerPosition = duration - timerAtPause;
    }
    angle = -90 - (timerPosition / duration) * 360;
    center = ofPoint(3 * (1920 / 4), 1080 / 2);
    int minutes = int(timerPosition / 60);
    int seconds = ceil(timerPosition - minutes*60);
    displayValue = ofToString(minutes, 2, '0') + ":" + ofToString(seconds, 2, '0');
    
//    ofImage img;
//    ofPixels pixels;
//    img.grabScreen(0, 0, 1920, 1080);
//    pixels = img.getPixels();
//    pixels.setNumChannels(3);
//    cout << "Number of channels: " << pixels.getNumChannels() << endl;
//    vidRecorder.addFrame(img.getPixels());
    
    // drawFbo();
    
//    rgbFbo.readToPixels(pixels);
//    vidRecorder.addFrame(pixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
ofPushMatrix();
   ofScale(0.5, 0.5);
//    rgbFbo.draw(0,0);

    
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
    
        ofPopMatrix();
    
}

void ofApp::drawFbo() {
    rgbFbo.begin();
    
    ofClear(0,0,0);
    
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
    
    rgbFbo.end();
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
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
        case 'c':
            vidRecorder.close();
            break;
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
