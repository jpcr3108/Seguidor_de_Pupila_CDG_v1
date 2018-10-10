#include "seleccion.h"

//--------------------------------------------------------------
void seleccion::setup() {

	tema = new ofxDatGuiThemeCharcoalMod(18);

	button1 = new ofxDatGuiButton("Generar");
	button2= new ofxDatGuiButton("Cargar");
	
	button1->onButtonEvent(this, &seleccion::onButtonEvent);
	button2->onButtonEvent(this, &seleccion::onButtonEvent);

	button1->setTheme(tema);
	button2->setTheme(tema);

	button1->setWidth(500, 1);
	button1->setHeight(100);
	button2->setWidth(500, 1);
	button2->setHeight(100);

	int w = ofGetWidth();
	int h = ofGetHeight();

	button1->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button2->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	button1->setPosition(w/2-250, h/2-120);
	button2->setPosition(w/2-250, h/2+20);

	
	Generar = FALSE;
	Cargar = FALSE;
	
	/*{ new ofxDatGuiTheme(true),
		new ofxDatGuiThemeSmoke(),
		new ofxDatGuiThemeWireframe(),
		new ofxDatGuiThemeMidnight(),
		new ofxDatGuiThemeAqua(),
		new ofxDatGuiThemeCharcoal(),
		new ofxDatGuiThemeAutumn(),
		new ofxDatGuiThemeCandy() };*/
	
}

//--------------------------------------------------------------
void seleccion::update() {
	button1->update();
	button2->update();
}

//--------------------------------------------------------------
void seleccion::draw() {
	button1->draw();
	button2->draw();
}

//--------------------------------------------------------------
void seleccion::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void seleccion::keyReleased(int key) {

}

//--------------------------------------------------------------
void seleccion::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void seleccion::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void seleccion::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void seleccion::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void seleccion::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void seleccion::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void seleccion::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void seleccion::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void seleccion::dragEvent(ofDragInfo dragInfo) {

}

void seleccion::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->is("Generar")) {
		cout << "Generar was clicked" << endl;
		Generar = TRUE;
		Cargar = FALSE;
	}
	else if (e.target->is("Cargar")) {
		cout << "Cargar was clicked" << endl;
		Generar = FALSE;
		Cargar = TRUE;
	}
}