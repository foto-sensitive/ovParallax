#pragma once

#include "ofMain.h"
#include "ovWrap.h"
#include "ofxGui.h"
#include "ofxImageSequence.h"
#include "ofxImageSequenceRecorder.h"

#define NWRAPS 2

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		double phasor(double frequency, double startphase, double endphase);
		void GUI(); //Displays rotation

		//Adds camera and controls
		ofEasyCam cam;

		//Video Background
		ofVideoPlayer bg;

		//360 Vision
		GLUquadricObj *quadric;

		//Iterators
		int i, j, u; 

		//Sequencing Images
		ofxImageSequence sequence;
		ofDirectory dir;
		double phase;

		//360° Unwrap objects
		ovWrap myWrap[NWRAPS];
		
		//GUI
		ofxPanel gui;
		ofxIntSlider parallax;
};
