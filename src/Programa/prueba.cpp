#include "prueba.h"
#include "stdio.h"
#include "calibrationManager.h"
#include "ofApp.h"
#include "ofxXmlSettings.h"



//--------------------------------------------------------------
void prueba::setup() {
	
	//ocra7.loadFont("fonts/OCRAStd.otf", 7);
	//ocra8.loadFont("fonts/OCRAStd.otf", 8);
	//ocra9.loadFont("fonts/OCRAStd.otf", 9);
	//ocra11.loadFont("fonts/OCRAStd.otf", 11);
	ocra13.loadFont("fonts/OCRAStd.otf", 26);
	bEjecucion = TRUE;
	bInicio = TRUE;
	nP = 0;
	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);
}

//--------------------------------------------------------------
void prueba::update() {
	
}


//--------------------------------------------------------------
void prueba::draw() {
	if (bEjecucion) {
		imagen.load(path_imagen);
		
		bEjecucion = FALSE;
	}
	

	if (bndTomaDatos) {
		
		xml.addTag("pt");
		xml.pushTag("pt", nP);
		xml.addValue("x", (int)posOjoX);
		xml.addValue("y", (int)posOjoY);
		xml.popTag();
		nP = nP + 1;
		nPP = nP;
		
	}

	if (bndTomaDatos == false && nP>0) {
		
		xml.saveFile("settings/puntos.xml");
		nPP = nP;
	}

	if (w>imagen.getWidth() || h>imagen.getHeight())
	{
		float fW = (w + 0.0f) / imagen.getWidth();
		float fH = (h + 0.0f) / imagen.getHeight();
		if (fW<fH)
		{
			int hDraw = imagen.getHeight()*fW;
			int wDraw = imagen.getWidth()*fW;
			imagen.draw(0, h / 2 - hDraw / 2, wDraw, hDraw);
		}
		else
		{
			int hDraw = imagen.getHeight()*fH;
			int wDraw = imagen.getWidth()*fH;
			imagen.draw(w / 2 - wDraw / 2, 0, wDraw, hDraw);
		}
	}
	else
	{
		imagen.draw(0, 0, w, h);
	}
}

//--------------------------------------------------------------
void prueba::keyPressed(int key) {

}

//--------------------------------------------------------------
void prueba::keyReleased(int key) {

}

//--------------------------------------------------------------
void prueba::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void prueba::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void prueba::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void prueba::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void prueba::resized(int w, int h) {

}
