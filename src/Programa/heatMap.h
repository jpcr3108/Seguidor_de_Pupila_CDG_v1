#pragma once
#define HEATMAP_H_INCLUDED
#include "ofMain.h"
#include "ofxXmlSettings.h"
class heatMap : public ofBaseApp {

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

	bool bEjecucion;
	float posOjoX;
	float posOjoY;
	int nPX;
	int nP;
	int mayor;
	int menor;
	int h;
	int w;
	int cont;
	int a;
	int b;
	int pX;
	int pY;
	static const int filas = 50;
	static const int columnas = 50;
	int matrizCuadros[filas][columnas];

	string path_imagen;
	string path_imagen_resultado;
	
	ofImage imagen;
	ofImage captura;
	ofImage mapaCalor;
	ofImage escala;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13, ocra15;
	ofxXmlSettings xml;

	ofxXmlSettings datos_usuario;

	int cont_pos;


};
