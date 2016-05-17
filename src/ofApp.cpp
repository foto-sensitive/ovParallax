

/*Created by Robert Pavlovskis on 02/03/2016
This is example shows how you can apply Parallax Scroll to 360° media.
Use the slider to adjust the ratio which determines the scroll different layers.*/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	//Prepare 360° unwrap objects
	for (i = 0; i < NWRAPS; i++)
		myWrap[i].setup(quadric);

	//Get image sequence directory
	dir.listDir("seq5");
	//Prepare image sequence
	sequence.loadSequence("seq5/frame", "png", 0, dir.size() - 1, 4);
	//this way there is no stutter when loading frames
	sequence.preloadAllFrames();	
	//Set to five frames per second
	sequence.setFrameRate(5); 

	/*Demo videos are too large for github,
	this will show up as blank unless you drag & drop a 360 video of your own to the window
	or go to www.mediafire.com/url to download the demos I made for this purpose.*/
	bg.loadMovie("sci_cube.avi");
	bg.setLoopState(OF_LOOP_NORMAL);
	bg.play();

	//Place camera inside sphere at 0,0,0
	cam.setAutoDistance(false);

	//GUI
	gui.setup();
	gui.add(parallax.setup("Parallax", 150, -200, 200));
	gui.setPosition(ofGetWidth()*0.0125, ofGetHeight()*0.11);

	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){

	bg.update();

	//Play image sequence through the use of phasor
	sequence.getFrameAtPercent(phasor(0.005, 0, 1))->draw(0, 0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	

	//Place camera inside the sphere
	cam.begin();

	ofPushMatrix();
	ofRotateX(270);

	//Map 360° Background texture to sphere
	myWrap[0].draw(0, &bg, 0.5, 300);
	
	//Orient the sphere in relation to camera movement, creates parallax scroll
	ofPushMatrix();
	ofRotateX(ofMap(cam.getGlobalOrientation().x(), -1, 1, -1, 1)*parallax);
	ofRotateY(ofMap(cam.getGlobalOrientation().y(), -1, 1, -1, 1)*parallax);
	ofRotateZ(ofMap(cam.getGlobalOrientation().z(), -1, 1, -1, 1)*parallax);

	myWrap[1].draw(1, &sequence, 0.75, 200);

	ofPopMatrix();
	ofPopMatrix();

	cam.end();

	GUI();

	gui.draw();
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

//--------------------------------------------------------------

double ofApp::phasor(double frequency, double startphase, double endphase) {
	//This is a phasor that takes a value for the start and end of the ramp. 
	if (phase<startphase) {
		phase = startphase;
	}
	if (phase >= endphase) phase = startphase;
	phase += ((endphase - startphase) / (1 / (frequency)));
	return(phase);
}

//--------------------------------------------------------------
void ofApp::GUI() {

	ofSetColor(0, 130);
	ofRect(10, 10, 357, 230);
	ofSetColor(255);

	//Tooltip
	ofDrawBitmapString("Use  the  slider to  adjust the  ratio  of", 20, 30);
	ofDrawBitmapString("parallax scroll, Drag the mouse across the", 20, 50);
	ofDrawBitmapString("screen to look around.", 20, 70);


	//Display Orientation
	ofDrawBitmapString("Rotation Orientation: ", 15, 15 + 130);
	string msg = std::to_string(cam.getGlobalOrientation().x());
	ofDrawBitmapString("X1:" + msg, 15, 15 + 160);
	msg = std::to_string(cam.getGlobalOrientation().y());
	ofDrawBitmapString("Y1:" + msg, 15, 15 + 180);
	msg = std::to_string(cam.getGlobalOrientation().z());
	ofDrawBitmapString("Z1:" + msg, 15, 15 + 200);

	msg = std::to_string(ofMap(cam.getGlobalOrientation().x(), -1, 1, 1, -1));
	ofDrawBitmapString("X2:" + msg, 140, 15 + 160);
	msg = std::to_string(ofMap(cam.getGlobalOrientation().y(), -1, 1, 1, -1));
	ofDrawBitmapString("Y2:" + msg, 140, 15 + 180);
	msg = std::to_string(ofMap(cam.getGlobalOrientation().z(), -1, 1, 1, -1));
	ofDrawBitmapString("Z2:" + msg, 140, 15 + 200);

}