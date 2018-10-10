#include "stdio.h"
#include "splashScreen.h"


void splashScreen::setup() {
	logo.loadImage("images/logo.png");
	ocra13.loadFont("fonts/OCRAStd.otf", 13);
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	bEjecucion = true;
}

void splashScreen::update() {
}

void splashScreen::draw() {
	

	// Titulo
	ofSetColor(255, 255, 255);
	ocra13.drawString("ANALISIS PUBLICITARIO", ofGetWidth()/2-124, 30);
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	logo.draw(ofGetWidth()/2-200, ofGetHeight()/2-100, 400, 200);

	if (bEjecucion) {

		t = ofGetElapsedTimef();
		bEjecucion = false;
	}

}

void splashScreen::keyPressed(int key) {

}

//--------------------------------------------------------------
void splashScreen::keyReleased(int key) {

}

//---------------------------p-----------------------------------
void splashScreen::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void splashScreen::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void splashScreen::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void splashScreen::mouseReleased(int x, int y, int button) {

}