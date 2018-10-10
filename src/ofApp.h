#pragma once

#define _TEST_APP


#include "ofMain.h"
#include "trackingManager.h"
#include "calibrationManager.h"
#include "buttonTrigger.h"
#include "splashScreen.h"
#include "prepPrueba.h"
#include "prueba.h"
#include "finPrueba.h"
#include "heatMap.h"
#include "welcome.h"
#include "seleccion.h"
#include "registroUsuario.h"
#include "SegCheck.h"
#include "ultimaPrueba.h"
#include "trayectoriaLinea.h"

enum {

	MODE_SPLASH, MODE_WELCOME, MODE_SEL, MODE_REGISTRO, MODE_SEG, MODE_TRACKING, MODE_CALIBRATING, MODE_TEST, MODE_PREP, MODE_PRUEBA, MODE_FIN, MODE_HEATMAP,MODE_TL,MODE_UPR
	
	
	//esto le asigna un numero a cada modo

};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		/*  existen 4 escenas:
		un administrador del seguidor de retina, un calibrador, un entrenador y un programa
		se crean atajos:
		*/
		trackingManager			TM;
		calibrationManager		CM;
		buttonTrigger			BT;
		splashScreen            SS;
		prepPrueba              PP;
		prueba                  PX;
		finPrueba               FP;
		heatMap                 HM;
		welcome					WM;
		seleccion				SL;
		registroUsuario			RU;
		SegCheck				SC;
		ultimaPrueba			UP;
		trayectoriaLinea		TL;
		

		//objetos de tipo ofPoint (tres coordenadas), describen la posicion de la retina
		ofPoint eyeSmoothed;
		ofPoint posOjo;

		ofParameter<int> ojoX;
		ofParameter<int> ojoY;

		//float t;
		//modo seleccionado
		int mode;
		float tiempo_inicio;
		float tiempo_guardado;

		bool Termine;

};
