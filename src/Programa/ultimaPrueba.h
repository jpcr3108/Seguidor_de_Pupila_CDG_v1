#pragma once
#define ULTIMAPRUEBA_H_INCLUDE
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxXmlSettings.h"

class ultimaPrueba : public ofBaseApp {
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

	void onButtonEvent(ofxDatGuiButtonEvent e);
	void onTextInputEvent(ofxDatGuiTextInputEvent e);

	void Busqueda(int id);

	ofImage imagen;

	ofxDatGuiLabel* label_ID;
	ofxDatGuiLabel* label_nombre;
	ofxDatGuiLabel* label_apellido;
	ofxDatGuiLabel* label_edad;
	ofxDatGuiLabel* label_genero;
	ofxDatGuiLabel* label_pp;
	ofxDatGuiLabel* label_pmv;

	ofxDatGuiButton* buscar;
	ofxDatGuiButton* flecha_izq;
	ofxDatGuiButton* flecha_der;

	ofxDatGuiTextInput* input_ID;

	ofxDatGuiFolder* datos_usuario;
	ofxDatGuiFolder* buscador;

	ofxDatGuiTheme* tema;
	ofxDatGuiTheme* tema_label;

	float t;
	bool bEjecucion;
	
	bool Buscar_b;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13, ocrabig;

	ofxXmlSettings xml_datos_usuario;
	int cont_pos;
	int size_xml;

	int primerID;
	int ultimoID;

};