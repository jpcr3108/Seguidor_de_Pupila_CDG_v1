#include "ofApp.h"
#include "stdio.h"
#include "ofxXmlSettings.h"
#include "splashScreen.h"
#include "prepPrueba.h"
#include "prueba.h"
#include "finPrueba.h"
#include "heatMap.h"
#include "welcome.h"

//--------------------------------------------------------------
void ofApp::setup(){
	Termine = false;
	
	//---- realiza la configuracion principal

	ofSetVerticalSync(true);

	mode = MODE_SPLASH;//modo inicial

	 //realiza el setup de los subprogramas
	TM.setup();
	CM.setup();
	SS.setup();
	PP.setup();
	RU.setup();
	PX.setup();
	FP.setup();
	HM.setup();
	WM.setup();
	SL.setup();
	SC.setup();
	UP.setup();
	TL.setup();
	

	//inicialización de varibles
	eyeSmoothed.set(0, 0, 0);
	posOjo.set(0, 0, 0);

	//ubica el primer recuadro del entrenador y el mensaje que sera visualizado
	BT.setup("¡MIRAME!", 50, 50, 180, 180);

}

//--------------------------------------------------------------
void ofApp::update(){

	//borra todo lo dibujado en el frame anterior
	ofBackground(70, 70, 70);
	

	// actualizar el tracker (e internamente el administrador de entrada)
	TM.update();

	// actualizar el calibrador
	CM.update();

	//actualiza modulos
	SS.update();
	PP.update();
	PX.update();
	FP.update();
	HM.update();
	WM.update();
	SL.update();
	RU.update();
	SC.update();
	UP.update();
	//if (mode == MODE_TL) {
	TL.update(); 
	//}
	

	// registra la posicion de ojo relacionando el CM con el TM
	if (CM.bAutomatic == true && CM.bAmInAutodrive == true && CM.bInAutoRecording) {

		if (TM.bGotAnEyeThisFrame()) {
			ofPoint trackedEye = TM.getEyePoint();
			CM.registerCalibrationInput(trackedEye.x, trackedEye.y);
		}

	}

	/*
	toma los datos de las posiciones del ojo en un tiempo determinado para realizar un promedio,
	esta nueva posicion promediada es grabada en el objeto eyeSmoothed
	ya que se trata de un promedio esto filtra los movimientos bruscos y suaviza las trayectorias del cursor
	*/
	if (CM.bBeenFit) {
		ofPoint trackedEye = TM.getEyePoint();
		ofPoint screenPoint = CM.getCalibratedPoint(trackedEye.x, trackedEye.y);
		eyeSmoothed.x = CM.smoothing * eyeSmoothed.x + (1 - CM.smoothing) * screenPoint.x;
		eyeSmoothed.y = CM.smoothing * eyeSmoothed.y + (1 - CM.smoothing) * screenPoint.y;
	}
	//ubica los nuevas posiciones aleatorias de los botones del entrenador
	if (mode == MODE_TEST) {
		ofPoint pt = eyeSmoothed;
		if (BT.update(pt.x, pt.y)) {
			BT.x = ofRandom(100, ofGetWidth() - 100);
			BT.y = ofRandom(100, ofGetHeight() - 100);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255, 255, 255);

	if (mode == MODE_REGISTRO) {
		if (RU.yaLei) {
			PX.path_imagen = RU.path_imagen;
			HM.path_imagen = RU.path_imagen;
			TL.path_imagen = RU.path_imagen;
		}
	}
	

	//dependiendo del modo que este activado, selecciona lo que debe dibujar
	if (mode == MODE_SPLASH)             SS.draw();
	if (mode == MODE_TRACKING)			TM.draw();
	if (mode == MODE_CALIBRATING)		CM.draw();
	if (mode == MODE_TEST)				BT.draw();
	if (mode == MODE_PREP)              PP.draw();
	if (mode == MODE_PRUEBA)            PX.draw();
	if (mode == MODE_FIN)               FP.draw();
	if (mode == MODE_HEATMAP)           HM.draw();
	if (mode == MODE_WELCOME)           WM.draw();
	if (mode == MODE_SEL)				SL.draw();
	if (mode == MODE_REGISTRO)			RU.draw();
	if (mode == MODE_SEG)				SC.draw();
	if (mode == MODE_UPR)				UP.draw();
	if (mode == MODE_TL)				TL.draw();
	//Temporizacion 4 segundos
	if (mode == MODE_SPLASH) {
		
		if (ofGetElapsedTimef() - SS.t > 4) {
			mode++;
		}
	}
	if (mode == MODE_PRUEBA && PX.bndTomaDatos) {
		if (ofGetElapsedTimef() - tiempo_inicio > PP.tp) {
			
				PX.bndTomaDatos = false;
				FP.nPX = PX.nPP;
				HM.nPX = PX.nPP;
				TL.nPX = PX.nPP;
				tiempo_guardado = ofGetElapsedTimef();
				//mode++;
				Termine = true;
			
		}
	}
	if (mode == MODE_PRUEBA && Termine) {
		if (ofGetElapsedTimef() - tiempo_guardado > 0.1) {
			mode++;
			Termine = false;
		}
	
	}
	if (mode == MODE_SEL) {
		SL.button1->setEnabled(TRUE);
		SL.button2->setEnabled(TRUE);
		RU.boton_guardar->setEnabled(FALSE);
		RU.boton_editar->setEnabled(FALSE);
		RU.boton_inicio->setEnabled(FALSE);
		RU.abrir_archivo->setEnabled(FALSE);
		RU.datos_usuario->setEnabled(FALSE);
		RU.label_datos_usuario->setEnabled(FALSE);
		RU.genero->setEnabled(FALSE);
		RU.modo_prueba->setEnabled(FALSE);
		RU.tiempo_prueba->setEnabled(FALSE);
		UP.datos_usuario->setEnabled(FALSE);
		UP.buscador->setEnabled(FALSE);
		UP.flecha_der->setEnabled(FALSE);
		UP.flecha_izq->setEnabled(FALSE);
		TM.camara->setEnabled(FALSE);
		if (SL.Generar) {
			mode++; 
			SL.Generar = FALSE;
		}
		if (SL.Cargar) {
			mode = MODE_UPR;
			SL.Cargar = FALSE;
		}
	}
		
	if (mode == MODE_REGISTRO) {
		SL.button1->setEnabled(FALSE);
		SL.button2->setEnabled(FALSE);
		RU.boton_guardar->setVisible(TRUE);
		RU.boton_guardar->setEnabled(TRUE);
		RU.boton_editar->setEnabled(TRUE);
		RU.boton_editar->setVisible(FALSE);
		RU.boton_inicio->setEnabled(TRUE);
		RU.boton_inicio->setVisible(FALSE);
		RU.datos_usuario->setVisible(TRUE);
		RU.tiempo_prueba->setEnabled(TRUE);
		RU.tiempo_prueba->setVisible(FALSE);
		RU.modo_prueba->setEnabled(TRUE);
		RU.modo_prueba->setVisible(FALSE);
		RU.genero->setVisible(TRUE);
		UP.datos_usuario->setEnabled(FALSE);
		UP.buscador->setEnabled(FALSE);
		UP.flecha_der->setEnabled(FALSE);
		UP.flecha_izq->setEnabled(FALSE);
		TM.camara->setEnabled(FALSE);

		if (RU.Guardar) {
			RU.Editar = FALSE;
			RU.boton_guardar->setVisible(FALSE);
			RU.boton_editar->setVisible(TRUE);
			RU.datos_usuario->setVisible(FALSE);
			RU.genero->setVisible(FALSE);
			
		}
		if (RU.Guardar && RU.yaLei) {
			RU.tiempo_prueba->setVisible(TRUE);
			RU.modo_prueba->setVisible(TRUE);
		}
		if (RU.Guardar && RU.yaLei && RU.yaTiempo && RU.modo_imagen) {
			RU.boton_inicio->setVisible(TRUE);
		}
		if (RU.Editar){			
			RU.datos_usuario->setVisible(TRUE);
			RU.genero->setVisible(TRUE);			
		}
		if (RU.Inicio) {
			mode++;
			FP.cont_pos = RU.cont_pos-1;
			HM.cont_pos = RU.cont_pos-1;
			UP.cont_pos = RU.cont_pos - 1;
			PP.cont_pos = RU.cont_pos - 1;
			TL.cont_pos = RU.cont_pos - 1;
		}
		RU.abrir_archivo->setEnabled(TRUE);
		RU.datos_usuario->setEnabled(TRUE);
		RU.label_datos_usuario->setEnabled(TRUE);
		RU.genero->setEnabled(TRUE);
		RU.modo_prueba->setEnabled(TRUE);
		
	}
	if (mode == MODE_UPR) {
		SL.button1->setEnabled(FALSE);
		SL.button2->setEnabled(FALSE);
		RU.boton_guardar->setEnabled(FALSE);
		RU.boton_editar->setEnabled(FALSE);
		RU.boton_inicio->setEnabled(FALSE);
		RU.abrir_archivo->setEnabled(FALSE);
		RU.datos_usuario->setEnabled(FALSE);
		RU.label_datos_usuario->setEnabled(FALSE);
		RU.genero->setEnabled(FALSE);
		RU.modo_prueba->setEnabled(FALSE);
		RU.tiempo_prueba->setEnabled(FALSE);
		UP.datos_usuario->setEnabled(TRUE);
		UP.buscador->setEnabled(TRUE);
		UP.flecha_der->setEnabled(TRUE);
		UP.flecha_izq->setEnabled(TRUE);
		TM.camara->setEnabled(FALSE);
	}
	if (mode != MODE_TL) {
		ofSetLineWidth(1);
	}

	if (mode == MODE_TRACKING) {

		SL.button1->setEnabled(FALSE);
		SL.button2->setEnabled(FALSE);
		RU.boton_guardar->setEnabled(FALSE);
		RU.boton_editar->setEnabled(FALSE);
		RU.boton_inicio->setEnabled(FALSE);
		RU.abrir_archivo->setEnabled(FALSE);
		RU.datos_usuario->setEnabled(FALSE);
		RU.label_datos_usuario->setEnabled(FALSE);
		RU.genero->setEnabled(FALSE);
		RU.modo_prueba->setEnabled(FALSE);
		RU.tiempo_prueba->setEnabled(FALSE);
		UP.datos_usuario->setEnabled(FALSE);
		UP.buscador->setEnabled(FALSE);
		UP.flecha_der->setEnabled(FALSE);
		UP.flecha_izq->setEnabled(FALSE);
		TM.camara->setEnabled(TRUE);

	}

	if (mode !=MODE_SEL && mode !=MODE_REGISTRO && mode != MODE_UPR && mode != MODE_TRACKING) {
		SL.button1->setEnabled(FALSE);
		SL.button2->setEnabled(FALSE);
		RU.boton_guardar->setEnabled(FALSE);
		RU.boton_editar->setEnabled(FALSE);
		RU.boton_inicio->setEnabled(FALSE);
		RU.abrir_archivo->setEnabled(FALSE);
		RU.datos_usuario->setEnabled(FALSE);
		RU.label_datos_usuario->setEnabled(FALSE);
		RU.genero->setEnabled(FALSE);
		RU.modo_prueba->setEnabled(FALSE);
		RU.tiempo_prueba->setEnabled(FALSE);
		UP.datos_usuario->setEnabled(FALSE);
		UP.buscador->setEnabled(FALSE);
		UP.flecha_der->setEnabled(FALSE);
		UP.flecha_izq->setEnabled(FALSE);
		TM.camara->setEnabled(FALSE);
	}
	

	// dibuja un circulo como cursor
	if (CM.bBeenFit) {
		ofSetColor(0, 0, 200, 120);
		ofFill();
		ofCircle(eyeSmoothed.x, eyeSmoothed.y, 20);
		int i = (int)(eyeSmoothed.x);
		int j = (int)eyeSmoothed.y;
		ojoX.set(i);
		ojoY.set(j);
		//se lee el archivo de configuraciones
		ofxXmlSettings XML;
		XML.loadFile("settings/miscSettings.xml");
		int cursorControl = XML.getValue("app:cursor:mode", 0);

		//si el control de cursor del computador esta activo posiciona el cursor en las coordenadas del ojo
		if (cursorControl == 1) {
			SetCursorPos(ojoX, ojoY);
		}
		
	}
	
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//Interrupciones por eventos del teclado
	switch (key) {

	case	OF_KEY_RIGHT:
		if (mode != MODE_SPLASH && mode != MODE_SEL && mode!= MODE_REGISTRO) {
			mode++;
			if (mode == 13) {
				mode = 2;  //reinicia variable al llegar al numero de programas
				CM.bBeenFit = false;
				PX.nP = 0;
				PX.xml.clear();
				FP.bEjecucion = true;
				HM.bEjecucion = true;
				UP.bEjecucion = true;
				PX.bEjecucion = true;
				PX.bInicio = true;
				PP.bEjecucion = true;
				TL.bEjecucion = true;
				TL.espereme = false;
				TL.linea.clear();
				Termine = false;
				RU.bID = TRUE;
				RU.Guardar = FALSE;
				RU.Editar = FALSE;
				RU.Inicio = FALSE;
				UP.Buscar_b = FALSE;
				//RU.yaTiempo = FALSE;
				//RU.modo_imagen = FALSE;
				FP.cuadros.clear();
			}
			if (mode == 14) {
				mode = 2;  //reinicia variable al llegar al numero de programas
				CM.bBeenFit = false;
				PX.nP = 0;
				PX.xml.clear();
				FP.bEjecucion = true;
				HM.bEjecucion = true;
				UP.bEjecucion = true;
				PX.bEjecucion = true;
				PX.bInicio = true;
				PP.bEjecucion = true;
				TL.bEjecucion = true;
				TL.espereme = false;
				TL.linea.clear();
				Termine = false;
				RU.bID = TRUE;
				RU.Guardar = FALSE;
				RU.Editar = FALSE;
				RU.Inicio = FALSE;
				UP.Buscar_b = FALSE;
				//RU.yaTiempo = FALSE;
				//RU.modo_imagen = FALSE;
				FP.cuadros.clear();
			}
		}
		break;
	case    OF_KEY_LEFT:
		if (mode == MODE_WELCOME)
		{
			mode = MODE_HEATMAP;
		}
		else if (mode == MODE_TL || mode == MODE_UPR || mode == MODE_SEG || mode == MODE_REGISTRO || mode == MODE_TRACKING || mode == MODE_CALIBRATING || mode == MODE_PREP || mode == MODE_PRUEBA || mode == MODE_HEATMAP || mode == MODE_SEL)
		{
			mode--;
		}
		else if (mode == MODE_TEST)
		{
			mode--;
			CM.bBeenFit = false;
			ofShowCursor();
		}
		break;
	case	OF_KEY_F1:
		ofToggleFullscreen();
		break;
	case    'a':
	case    'A':
		WM.acercaImg = true;
		break;
	case    'c':
	case    'C':
		WM.acercaImg = false;
		break;
	case    'i':
	case    'I':
		if (mode == MODE_PRUEBA)
		{
			PX.bndTomaDatos = true;
			tiempo_inicio = ofGetElapsedTimef();
						
		}
		break;
	/*case    't':
	case    'T':
		if (mode == MODE_PRUEBA)
		{
			PX.bndTomaDatos = false;
			FP.nPX = PX.nPP;
			HM.nPX = PX.nPP;
		}
		break;*/
	}

	if (mode == MODE_CALIBRATING) {
		CM.keyPressed(key);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
	if (mode == MODE_PREP) {
		PP.posOjoX = x;
		PP.posOjoY = y;
	}
	if (mode == MODE_PRUEBA) {
		PX.posOjoX = x;
		PX.posOjoY = y;
	}
	if (mode == MODE_FIN) {
		FP.posOjoX = x;
		FP.posOjoY = y;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//eventos de mouse
	if (mode == MODE_TRACKING)			TM.mouseDragged(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//eventos de mouse
	if (mode == MODE_TRACKING)			TM.mousePressed(x, y, button);
	if (mode == MODE_CALIBRATING)		CM.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//eventos de mouse
	if (mode == MODE_TRACKING)			TM.mouseReleased();
	if (mode == MODE_CALIBRATING)		CM.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
