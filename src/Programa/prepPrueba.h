#pragma once
#define _PREPPRUEBA
#include "ofMain.h"
#include "ofxXmlSettings.h"

class prepPrueba : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void savePoints();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13;
	float posOjoX;
	float posOjoY;
	

	int modePG;
	int w;
	int h;
	int nM;
	int cont_pos;
	int tp;
	bool bndTomaDatos;
	bool bEjecucion;

	ofxXmlSettings datos_usuario;

};
