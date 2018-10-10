#pragma once
#define REGISTRO_H_INCLUDED
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxXmlSettings.h"

class registroUsuario : public ofBaseApp {
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
	void onTextInputEvent(ofxDatGuiTextInputEvent e);
	void onDropdownEvent(ofxDatGuiDropdownEvent e);

	bool yaLei;
	bool Inicio;
	bool Guardar;
	bool Editar;
	bool bID;
	bool modo_imagen;
	bool yaTiempo;

	int numeroID;
	int cont_pos;
	string tp;

	ofxXmlSettings xml_datos;
	ofxXmlSettings xml_ID;
	ofxXmlSettings xml_usuario_actual;

	
	ofTrueTypeFont ocra;

	string path_imagen;

	ofTrueTypeFont ocra7, ocra8, ocra9, ocra11, ocra13;

	ofxDatGuiButton* boton_guardar;
	ofxDatGuiButton* boton_editar;
	ofxDatGuiButton* boton_inicio;
	ofxDatGuiButton* abrir_archivo;
	
	ofxDatGuiTextInput* nombre;
	ofxDatGuiTextInput* apellido;
	ofxDatGuiTextInput* edad;
		
	ofxDatGuiDropdown* genero;
	ofxDatGuiDropdown* modo_prueba;

	ofxDatGuiLabel* ID;
	ofxDatGuiLabel* ID_mod;
	ofxDatGuiLabel* label_nombre;
	ofxDatGuiLabel* label_apellido;
	ofxDatGuiLabel* label_edad;
	ofxDatGuiLabel* label_genero;

	ofxDatGuiTextInput* tiempo_prueba;
	
	ofxDatGuiFolder* datos_usuario;
	ofxDatGuiFolder* label_datos_usuario;
	
	ofxDatGuiTheme* tema_carpeta;
	ofxDatGuiTheme* tema_input_listbox;
	ofxDatGuiTheme* tema_boton;
};