#include "stdio.h"
#include "welcome.h"


void welcome::setup() {
	imagen.loadImage("images/vision.png");
	ocra13.loadFont("fonts/OCRAStd.otf", 13);
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	ocraBig.loadFont("fonts/OCRAStd.otf", 30);
	acerca.loadImage("images/acerca.png");
	acercaImg = false;
	bEjecucion = true;
}

void welcome::update() {
}

void welcome::draw() {
	int w = ofGetWidth();
	int h = ofGetHeight();
	//caja info
	ofSetColor(0, 0, 0, 120); //negro transparentoso
	ofFill();
	ofRect(ofGetWidth() - 280, ofGetHeight() - 110, 280, 110);

	// Titulo
	ofSetColor(255, 255, 255);
	ocraBig.drawString("Bienvenido", w / 2 - 150, 130);
	ocra13.drawString("Este sofware se utiliza para realizar estudios de Neuromarketing relacionados con ", w / 2 - 533, 180);
	ocra13.drawString("movimiento ocular. Despues de seleccionar una imagen para el estudio, se realizan ", w / 2 - 533, 195);
	ocra13.drawString("dos pruebas: Mapa de Calor y Seguimiento de Trayectoria.", w / 2- 533, 210);
	ocra13.drawString("POR FAVOR,  PRESIONE LA FLECHA DERECHA PARA COMENZAR", w / 2-338, h-100);
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	
	imagen.draw(ofGetWidth() / 2 - 125, h - 250-200, 250, 250);

	//info
	ofSetColor(255, 255, 255);
	int wc = ofGetWidth() - 280;
	int hc = ofGetHeight() - 110;
	ocra8.drawString("Desarrollado por OTEC SAS", wc + 30, hc + 25);
	ocra7.drawString("2018", wc + 120, hc + 50);
	ocra8.drawString("(a)  -  about/acerca", wc + 40, hc + 100);


	if (acercaImg) {
		acerca.draw(ofGetWidth() / 2 - 400, ofGetHeight() / 2 - 250, 800, 500);

	}

}

void welcome::keyPressed(int key) {

}

//--------------------------------------------------------------
void welcome::keyReleased(int key) {

}

//---------------------------p-----------------------------------
void welcome::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void welcome::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void welcome::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void welcome::mouseReleased(int x, int y, int button) {

}