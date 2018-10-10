#pragma once
#define SPLASHSCREEN_H_INCLUDED
#include "ofMain.h"

class splashScreen : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);

	bool acercaImg;

	ofImage logo;
	

	float t;
	bool bEjecucion;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13;

};
