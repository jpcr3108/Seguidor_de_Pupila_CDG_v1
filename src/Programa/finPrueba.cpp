#include "finPrueba.h"
#include "stdio.h"
#include "calibrationManager.h"


//--------------------------------------------------------------
void finPrueba::setup() {

	//carga de fuentes
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	ocra9.loadFont("fonts/OCRAStd.otf", 9);
	ocra11.loadFont("fonts/OCRAStd.otf", 11);
	ocra13.loadFont("fonts/OCRAStd.otf", 13);
	ocra15.loadFont("fonts/OCRAStd.otf", 15);

	//Carga de imagenes
	
	bEjecucion = true;
	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);
	
}

//--------------------------------------------------------------
void finPrueba::update() {

}


//--------------------------------------------------------------
void finPrueba::draw() {

	if (bEjecucion) {

		int nP =  nPX;
		int *cxLoad= new int[nP];
		int *cyLoad= new int[nP];
		f = 0;
		c = 0;
		p = 0;
		a = w / n;
		b = h / m;
		xml.loadFile("settings/puntos.xml");
		for (int i = 0; i < nP; i++) {
			xml.pushTag("pt", i);
			cxLoad[i] = xml.getValue("x", 0);
			cyLoad[i] = xml.getValue("y", 0);
			xml.popTag();
		}

		for (int i = 0; i<m; i++) {
			for (int j = 0; j<n; j++) {
				matrizCuadros[i][j] = 0;
			}
		}
		while (p<nP) {
			if ((f*(a) <= cxLoad[p] && cxLoad[p] <= (f + 1)*(a)) && (c*(b) <= cyLoad[p] && cyLoad[p] <= (c + 1)*(b))) {
				p++;
				matrizCuadros[f][c]++;
				f = 0;
				c = 0;
			}
			else {
				if (f<n) {
					f++;
				}
				else {
					if (c<m) {
						f = 0;
						c++;
					}
					else {
						c = 0;
						f = 0;
					}

				}
			}
		}
		int cont = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j<n; j++) {
				cuadros.addTag("pt");
				cuadros.pushTag("pt", cont);
				cuadros.addValue("cr", matrizCuadros[i][j]);
				cuadros.popTag();
				cont++;
			}
		}
		cuadros.saveFile("settings/cuadros.xml");
		bEjecucion = false;

		ofxXmlSettings xmlAux;
		xmlAux.loadFile("settings/docAux.xml");
		xmlAux.pushTag("Aux");
		int aux = xmlAux.getValue("Aux", 0);
		xmlAux.popTag();

		datos_usuario.loadFile("settings/Datos_Usuarios.xml");
		datos_usuario.pushTag("datos", 0);
		datos_usuario.pushTag("usuario", cont_pos);
		datos_usuario.addValue("Primer_punto_X", cxLoad[1]);
		datos_usuario.addValue("Primer_punto_Y", cyLoad[1]);
		datos_usuario.popTag();
		datos_usuario.popTag();
		datos_usuario.saveFile("settings/Datos_Usuarios.xml");
		
	}

	ocra15.drawString("FIN DE LA PRUEBA", 70, 300);
	ocra15.drawString("MUCHAS GRACIAS POR SU PARTICIPACION", 70, 350);
	//ocra15.drawString(std::to_string(nPX), 70, 500);

}




//--------------------------------------------------------------
void finPrueba::keyPressed(int key) {

}

//--------------------------------------------------------------
void finPrueba::keyReleased(int key) {

}

//--------------------------------------------------------------
void finPrueba::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void finPrueba::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void finPrueba::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void finPrueba::mouseReleased(int x, int y, int button) {

}


//--------------------------------------------------------------
void finPrueba::resized(int w, int h) {

}
