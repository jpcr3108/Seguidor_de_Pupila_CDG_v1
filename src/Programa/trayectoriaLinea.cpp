#include "trayectoriaLinea.h"
#include "stdio.h"
#include "string.h"

void trayectoriaLinea::setup() {
	FPSp = 30; //FPS Programa
	ofSetFrameRate(FPSp);
	nPX = 1;
	seccionador = 5;
	mult = 1;
	bEjecucion = TRUE;
	espereme = FALSE;
	w = ofGetWidth();
	h = ofGetHeight();
	acum = 0;
	puntosX.resize(nPX);
	puntosY.resize(nPX);
	linea.setClosed(FALSE);
	w1 = GetSystemMetrics(SM_CXSCREEN);
	h1= GetSystemMetrics(SM_CYSCREEN);
	ofEnableAlphaBlending();

#ifdef TARGET_WIN32
	grabador.setFfmpegLocation("C:/openFrameworks/apps/Seguidor_de_Pupila_update_v1/Seguidor_de_Pupila_update_v1/bin/data/ffmpeg/bin/ffmpeg.exe"); // use this is you have ffmpeg installed in your data folder
#endif
	
	
}

void trayectoriaLinea::update() {

}

void trayectoriaLinea::draw() {
	ofEnableAlphaBlending();
	if (!bEjecucion) {
		if (acum < nPX) {
			linea.addVertex(puntosX[acum], puntosY[acum]);
			acum++;
		}
		ofSetColor(255, 255, 255);
		imagen.draw(0, 0, w, h);

		ofSetColor(0, 255, 0, 30);
		for (int i = 0; i < linea.getVertices().size(); i++) {
			ofDrawCircle(linea.getVertices()[i], 20);
		}
		ofSetColor(255, 0, 0);
		ofSetLineWidth(10);
		linea.getSmoothed(15, 0.2).draw();
		
		if (linea.size() == seccionador*mult) {
			
			captura.grabScreen(0, 0, 1364, 768, 1);
			grabador.addFrame(captura.getPixelsRef());
			mult++;
			
		}
		
		if (acum == nPX) {
			
			grabador.close();	


		}
		
		

	}
	path_video_resultado = "Video/Prueba_";
	if (bEjecucion) {
		acum = 0;
		seccionador = 5;
		mult = 1;
		imagen.load(path_imagen);
		
		datos();
		puntos.loadFile("settings/puntos.xml");

		puntosX.resize(puntos.getNumTags("pt"));
		puntosY.resize(puntos.getNumTags("pt"));

		for (int i = 0; i < nPX; i++) {
			puntos.pushTag("pt", i);
			puntosX[i] = puntos.getValue("x", 0);
			puntosY[i] = puntos.getValue("y", 0);
			puntos.popTag();
		}
		linea.setClosed(FALSE);
		
		bEjecucion = FALSE;
		espereme = TRUE;
		fileName = path_video_resultado;
		if (!grabador.isInitialized()) {
			grabador.setup(fileName, 1364, 768, FPSp/seccionador);
			grabador.start();		
		}
		
		
	}
	
	
	
}

void trayectoriaLinea::datos() {

	datos_usuario.loadFile("settings/Datos_Usuarios.xml");
	datos_usuario.pushTag("datos", 0);
	datos_usuario.pushTag("usuario", cont_pos);
	path_video_resultado = path_video_resultado + datos_usuario.getValue("ID", "");
	//path_video_resultado = path_video_resultado + "_" + datos_usuario.getValue("Nombre", "");
	//path_video_resultado = path_video_resultado + "_" + datos_usuario.getValue("Apellido", "");
	//path_video_resultado = path_video_resultado + ".mp4";

	/*fileName = datos_usuario.getValue("ID", "");
	fileName = fileName + "_" + datos_usuario.getValue("Nombre", "");
	fileName = fileName + "_" + datos_usuario.getValue("Apellido", "");
	cout << path_video_resultado << endl;*/
	datos_usuario.addValue("Video_Resultado", path_video_resultado);
	datos_usuario.popTag();
	datos_usuario.popTag();
	datos_usuario.saveFile("settings/Datos_Usuarios.xml");

}
