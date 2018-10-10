#pragma once
#define _PRUEBA
#include "ofMain.h"
#include "ofxXmlSettings.h"


class prueba : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	int modePX;
	int nP;
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	int w;
	int h;
	int tp;
	int t;
	bool bEjecucion;
	bool bInicio;

	ofImage imagen;
	string path_imagen;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13, ocra15;
	float posOjoX;
	float posOjoY;
	int nPP;
	ofxXmlSettings xml;
	bool bndTomaDatos;

	
	//int index;
};