#include "ofApp.h"
#include "prepPrueba.h"
#include "stdio.h"
#include "calibrationManager.h"
#include <wtypes.h>

//--------------------------------------------------------------
void prepPrueba::setup() {

	ofBackground(000, 153, 204);
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	ocra9.loadFont("fonts/OCRAStd.otf", 9);
	ocra11.loadFont("fonts/OCRAStd.otf", 11);
	ocra13.loadFont("fonts/OCRAStd.otf", 13);

	bEjecucion = true;
	
	
	//w = ofGetWidth(), h = ofGetHeight();
}

//--------------------------------------------------------------
void prepPrueba::update() {
}


//--------------------------------------------------------------
void prepPrueba::draw() {
	int w = ofGetWidth();
	int h = ofGetHeight();
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255); //blanco
	
							   //titulo

	ocra13.drawString("ANALISIS PUBLICITARIO", w*4/10, 30);
	

	ocra11.drawString("A continuacion se muestra un punto en la mitad de la pantalla", w/5, 95);
	ocra11.drawString("el cual requerimos que usted observe. Cuando tenga su atencion en este", w/5, 110);
	ocra11.drawString("por favor indicar al analista para que el inicie la prueba, la cual consiste", w/5, 125);
	ocra11.drawString("en que usted observe las partes de la imagen que mas le llamen la atencion.", w/5, 140);
	ofSetColor(255, 255, 255);
	ofFill();
	ofCircle(ofGetWidth()/2, ofGetHeight()/2, 20);
	if (bEjecucion) {
		datos_usuario.loadFile("settings/Datos_Usuarios.xml");
		datos_usuario.pushTag("datos", 0);
		datos_usuario.pushTag("usuario", cont_pos);
		tp = datos_usuario.getValue("Tiempo_prueba", 0);
		datos_usuario.popTag();
		datos_usuario.popTag();	
		bEjecucion = false;
	}
	
}

//--------------------------------------------------------------
void prepPrueba::keyPressed(int key) {
}

//--------------------------------------------------------------
void prepPrueba::keyReleased(int key) {

}

//--------------------------------------------------------------
void prepPrueba::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void prepPrueba::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void prepPrueba::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void prepPrueba::mouseReleased(int x, int y, int button) {

}


//--------------------------------------------------------------
void prepPrueba::resized(int w, int h) {

}
