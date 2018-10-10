#pragma once
#define TRAYLINEA_H_INCLUDED
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxVideoRecorder.h"

class trayectoriaLinea : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void datos();

	bool bEjecucion;
	bool espereme;

	int w;
	int h;
	int nPX;

	ofPolyline linea;
	
	vector<int> puntosX;
	vector<int> puntosY;

	int acum;
	int cont_pos;
	string path_imagen;
	string path_video_resultado;
	string fileName;

	ofImage imagen;
	ofImage	captura;
	

	ofxXmlSettings puntos;
	ofxXmlSettings datos_usuario;

	

	ofxVideoRecorder grabador;

	int w1;
	int h1;

	int seccionador;
	float FPSp;
	int mult;


};
