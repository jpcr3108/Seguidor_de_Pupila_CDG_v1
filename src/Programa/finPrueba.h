#pragma once
#define FINPRUEBA_H_INCLUDED
#include "ofxXmlSettings.h"
#include "ofMain.h"

class finPrueba : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13, ocra15;

	float posOjoX;
	float posOjoY;
	int nPX;

	ofxXmlSettings xml;
	ofxXmlSettings cuadros;
	ofxXmlSettings datos_usuario;

	bool bEjecucion;
	int nP;
	int f;
	int c;
	int p;
	static const int m = 50;
	static const int n = 50;
	int matrizCuadros[m][n];
	int h;
	int w;
	int a;
	int b;
	int cont_pos;
	
};