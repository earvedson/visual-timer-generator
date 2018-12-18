#pragma once

#include "ofMain.h"
#include "ofxVideoRecorder.h"
#include "ofQTKitGrabber.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawFbo();
        void exit();
        void reset();
        void startStop();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void audioIn(float * input, int bufferSize, int nChannels);

    
    bool isRunning;
    bool isPaused;
    float timerAtPause;
    
    
    
    // drawing the circle
    float duration;
    float timerPosition;
    float angle;
    ofPoint center;
    
    // counter
    ofTrueTypeFont futuraBold;
    string displayValue;
    
    // video
//    ofVideoGrabber      vidGrabber;
    ofxVideoRecorder    vidRecorder;
    ofSoundStream       soundStream;
    bool bRecording;
    int sampleRate;
    int channels;
    string fileName;
    string fileExt;
    
    void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
    
    int timerWidth;
    int timerHeight;
    
    ofFbo rgbFbo;
    ofPixels pixels;
    
};
