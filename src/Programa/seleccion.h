#pragma once
#define SELECCION_H_INCLUDED
#include "ofMain.h"
#include "ofxDatGui.h"

class seleccion : public ofBaseApp {
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
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);

	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void onButtonEvent(ofxDatGuiButtonEvent e);

	bool bEjecucion;
	bool Generar;
	bool Cargar;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13;

	ofxDatGuiButton* button1;
	ofxDatGuiButton* button2;

	ofxDatGuiTheme* tema;
};
