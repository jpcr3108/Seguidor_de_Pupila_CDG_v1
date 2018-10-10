#include "stdio.h"
#include "SegCheck.h"


void SegCheck::setup() {
	imagen.loadImage("images/warning-sign.png");
	ocra13.loadFont("fonts/OCRAStd.otf", 15);
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 20);
	ocraBig.loadFont("fonts/OCRAStd.otf", 30);
	bEjecucion = true;
}

void SegCheck::update() {
}

void SegCheck::draw() {
	int w = ofGetWidth();
	int h = ofGetHeight();
	
	// Titulo
	ofSetColor(255, 255, 255);
	ocraBig.drawString("AVISO DE SEGURIDAD", ofGetWidth() / 2 - 270, 80);
	ocra13.drawString("Por favor, antes de realizar la prueba:", w / 2-292, 150);
	ocra13.drawString("- Verificar que la diadema esta conectada al computador por un puerto USB.", w / 8, 200);
	ocra13.drawString("- Acomodar la diadema en la cabeza del usuario de manera comoda para el mismo.", w / 8, 230);
	ocra13.drawString("- Recordar al usuario no mover la cabeza durante la calibracion y la prueba.", w / 8, 260);

	ocra8.drawString("PULSE LA FLECHA DERECHA PARA COMENZAR", w / 2-370, h-100);
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);

	imagen.draw(ofGetWidth() / 2 - 128, ofGetHeight() / 2 - 60);

	
	
}

void SegCheck::keyPressed(int key) {

}

//--------------------------------------------------------------
void SegCheck::keyReleased(int key) {

}

//---------------------------p-----------------------------------
void SegCheck::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void SegCheck::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void SegCheck::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void SegCheck::mouseReleased(int x, int y, int button) {

}