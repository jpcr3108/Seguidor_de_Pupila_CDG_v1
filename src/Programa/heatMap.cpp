#include "heatMap.h"
#include "stdio.h"
#include "string.h"

//--------------------------------------------------------------
void heatMap::setup() {

	//carga de fuentes
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	ocra9.loadFont("fonts/OCRAStd.otf", 9);
	ocra11.loadFont("fonts/OCRAStd.otf", 11);
	ocra13.loadFont("fonts/OCRAStd.otf", 13);
	ocra15.loadFont("fonts/OCRAStd.otf", 15);
	
	escala.load("images/degradado.png");
	w = ofGetWidth();
	h = ofGetHeight();
	a = w / columnas;
	b = h / filas;

	//Contadores
	
	bEjecucion = true;
}

//--------------------------------------------------------------
void heatMap::update() {


}

//--------------------------------------------------------------
void heatMap::draw() {
	ofEnableAlphaBlending();
	if (bEjecucion) {
		imagen.load(path_imagen);
		ofBackground(255, 255, 255,0);
		nP = 0;
		int x = 0;
		int y = 0;
		mayor = 0;
		menor = INT_MAX;
		xml.loadFile("settings/cuadros.xml");
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j<columnas; j++) {
				xml.pushTag("pt", nP);
				matrizCuadros[i][j] = xml.getValue("cr", 0);
				xml.popTag();
				nP++;
				if (matrizCuadros[i][j]>mayor) {
					mayor = matrizCuadros[i][j];
					x = j;
					y = i;
				}
				if (matrizCuadros[i][j]>0 && matrizCuadros[i][j] < menor) {
					menor = matrizCuadros[i][j];
				
				}
			}
		}
		pX = ((a*y) + (a*(y + 1))) / 2;
		pY = ((b*x) + (b*(x + 1))) / 2;
		cont = 0;
		cout << mayor << "\n";
		cout << menor << endl;
		int centroX = 0;
		int centroY = 0;
		float valor = 0.0;
		while (cont<5)
		{
			for (int i = 0; i < filas; i++) {
				for (int j = 0; j<columnas; j++) {
					centroX = ((a*i) + (a*(i + 1))) / 2;
					centroY = ((b*j) + (b*(j + 1))) / 2;
					if (matrizCuadros[i][j]>0) {
						valor = (matrizCuadros[i][j] + 0.00) / mayor;
						if (0.0000f <= valor&& valor <= 0.2000f&&cont == 0) {
							ofSetColor(0, 255, 255);
							ofFill();
							ofCircle(centroX, centroY, 20 + 5);													
						}
						else if (0.2000f < valor && valor <= 0.4000f) {
							if (cont == 0)
							{
								ofSetColor(0, 255, 255);
								ofFill();
								ofCircle(centroX, centroY, 15 + 5);
							}
							if (cont == 1)
							{
								ofSetColor(0, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 10 + 5);
							}
						}
						else if (0.4000f < valor && valor <= 0.6000f) {
							if (cont == 0)
							{
								ofSetColor(0, 255, 255);
								ofFill();
								ofCircle(centroX, centroY, 20 + 5);
							}
							if (cont == 1)
							{
								ofSetColor(0, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 15 + 5);
							}
							if (cont == 2)
							{
								ofSetColor(255, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 10 + 5);
							}
						}
						else if (0.6000f < valor && valor <= 0.8000f) {
							if (cont == 0)
							{
								ofSetColor(0, 255, 255);
								ofFill();
								ofCircle(centroX, centroY, 25 + 5);
							}
							if (cont == 1)
							{
								ofSetColor(0, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 20 + 5);
							}
							if (cont == 2)
							{
								ofSetColor(255, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 15 + 5);
							}
							if (cont == 3)
							{
								ofSetColor(255, 128, 0);
								ofFill();
								ofCircle(centroX, centroY, 10 + 5);
							}
						}
						else if (0.8000f < valor && valor <= 1.0000f) {
							if (cont == 0)
							{
								ofSetColor(0, 255, 255);
								ofFill();
								ofCircle(centroX, centroY, 30 + 5);
							}
							if (cont == 1)
							{
								ofSetColor(0, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 25 + 5);
							}
							if (cont == 2)
							{
								ofSetColor(255, 255, 0);
								ofFill();
								ofCircle(centroX, centroY, 20 + 5);
							}
							if (cont == 3)
							{
								ofSetColor(255, 128, 0);
								ofFill();
								ofCircle(centroX, centroY, 15 + 5);
							}
							if (cont == 4)
							{
								ofSetColor(255, 0, 0);
								ofFill();
								ofCircle(centroX, centroY, 10 + 5);
							}
						}
					}
				}
			}
			cont++;
		}
		captura.grabScreen(0, 0, w, h,0);
		captura.saveImage("Resultados/resultado_heatmap.png");
		
		
	}
	ofBackground(70, 70, 70);
	ofSetColor(255, 255, 255, 255);
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
	captura.loadImage("Resultados/resultado_heatmap.png");
	ofSetColor(255, 255, 255, 170);
	captura.draw(0, 0, w, h);
	
	
	
	path_imagen_resultado = "C:/openFrameworks/apps/Seguidor_de_Pupila_update_v1/Seguidor_de_Pupila_update_v1/bin/data/Resultados/";
	
	//mapaCalor.saveImage(path_imagen_resultado);

	if (bEjecucion)
	{
		datos_usuario.loadFile("settings/Datos_Usuarios.xml");
		datos_usuario.pushTag("datos", 0);
		datos_usuario.pushTag("usuario", cont_pos);
		path_imagen_resultado = path_imagen_resultado + datos_usuario.getValue("ID", "");
		path_imagen_resultado = path_imagen_resultado + "_" + datos_usuario.getValue("Nombre", "");
		path_imagen_resultado = path_imagen_resultado + "_" + datos_usuario.getValue("Apellido", "");
		path_imagen_resultado = path_imagen_resultado + ".png";
		datos_usuario.addValue("Punto_Mas_Visto_X", pX);
		datos_usuario.addValue("Punto_Mas_Visto_Y", pY);
		datos_usuario.addValue("Imagen_Resultado", path_imagen_resultado);
		datos_usuario.popTag();
		datos_usuario.popTag();
		datos_usuario.saveFile("settings/Datos_Usuarios.xml");
		//imagen.draw(0, 0, w - 50, h);
		
		mapaCalor.grabScreen(0, 0, w, h,0);
		ofSetColor(70,70, 70);
		ofDrawRectangle(0, 0, w, h);
		ofSetColor(255, 255, 255);
		mapaCalor.draw(0, 0, w - 50, h);
		ofSetColor(255, 255, 255,170);
		escala.draw(ofGetWidth() - 50, 15, 50, ofGetHeight() - 30);
		ofSetColor(255, 255, 255);
		ocra13.drawString(std::to_string(mayor), ofGetWidth() - 50, 15);
		ocra13.drawString(std::to_string(menor), ofGetWidth() - 50, ofGetHeight() - 1);
		mapaCalor.grabScreen(0, 0, w, h,0);
		mapaCalor.saveImage(path_imagen_resultado);
		bEjecucion = false;
				
	}
	//ofSetColor(255, 255, 255);
	
	
	

}

//--------------------------------------------------------------
void heatMap::keyPressed(int key) {

}

//--------------------------------------------------------------
void heatMap::keyReleased(int key) {

}

//--------------------------------------------------------------
void heatMap::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void heatMap::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void heatMap::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void heatMap::mouseReleased(int x, int y, int button) {

}


//--------------------------------------------------------------
void heatMap::resized(int w, int h) {

}