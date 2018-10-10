#include "trackingManager.h"


void trackingManager::setup() {

	IM.setup(1);

	setupGui();

	vector<ofVideoDevice> devices = IM.vidGrabber.listDevices();
	vector<string> devicesNames;
	devicesNames.resize(devices.size());
	for (int i = 0; i < devices.size(); i++) {
		devicesNames[i] = devices[i].deviceName;
	}
	camara = new ofxDatGuiDropdown("Camara", devicesNames);
	camara->setTheme(new ofxDatGuiThemeCharcoalMod(10));
	camara->setWidth(300);
	camara->setPosition(700, 500);
	camara->setLabelUpperCase(FALSE);
	camara->onDropdownEvent(this, &trackingManager::onDropdownEvent);

	//--- set up tracking
	tracker.setup(IM.width, IM.height);
	minBlob = 10 * 10;
	maxBlob = 100 * 100;
	threshold = 21;

	bFoundEye = false;
	eyePoint.set(0, 0, 0);
}

void trackingManager::update() {
	//--- update video/camera input
	IM.update();
	camara->update();

	//--- eye tracking (on new frames)
	if (IM.bIsFrameNew) {
		trackEyes();
	}

	//--- gui
	panel.update();
	updateGui();


}



ofPoint	trackingManager::getEyePoint() {
	return eyePoint;
}

bool trackingManager::bGotAnEyeThisFrame() {
	return bFoundEye;
}

//--------------------------------------------------------------
void trackingManager::trackEyes() {
	tracker.update(IM.grayImage, threshold, minBlob, maxBlob, 0.5f);
	bFoundEye = tracker.bFoundOne;
	eyePoint = tracker.getEyePoint();
}


void trackingManager::setupGui() {

	panel.setup("Panel CV", 700, 20, 300, 450);
	panel.addPanel("Ajuste de Imagen", 1, false);
	panel.addPanel("Corrector de Bordes", 1, false);
	panel.addPanel("Detector Blobs", 1, false);

	/*if (IM.mode == INPUT_VIDEO) {
		panel.addPanel("Configurar Archivo Video", 1, false);
	}
	else {
		panel.addPanel("Configurar Video en Vivo", 1, false);
	}*/

	//---- gaze
	panel.setWhichPanel("Ajuste de Imagen");
	panel.setWhichColumn(0);

	panel.addToggle("Inv. horizontal ", "B_RIGHT_FLIP_X", false);
	panel.addToggle("Inv. vertical ", "B_RIGHT_FLIP_Y", false);

	panel.addToggle("Usar Contraste/ Brillo", "B_USE_CONTRAST", true);
	panel.addSlider("contraste ", "CONTRAST", 0.28f, 0.0, 1.0f, false);
	panel.addSlider("brillo ", "BRIGHTNESS", -0.02f, -1.0, 3.0f, false);

	panel.addToggle("usar gamma ", "B_USE_GAMMA", true);
	panel.addSlider("gamma ", "GAMMA", 0.57f, 0.01, 3.0f, false);

	panel.addSlider("umbral/ threshold ", "THRESHOLD_GAZE", threshold, 0, 255, true);




	panel.setWhichPanel("Detector Blobs");
	panel.addToggle("Usar dilatar", "B_USE_DILATE", true);
	panel.addSlider("Num. Dilataciones ", "N_DILATIONS", 0, 0, 10, true);
	panel.addSlider("Blob Min.", "MIN_BLOB", 10 * 10, 0, 5000, true);
	panel.addSlider("Blob Max.", "MAX_BLOB", 100 * 100, 0, 50500, true);

	//---- tracker edges
	panel.setWhichPanel("Corrector de Bordes");
	panel.setWhichColumn(0);
	panel.addSlider("Pos. X ", "EDGE_MASK_X", 320, 0, 640, true);
	panel.addSlider("Pos. Y ", "EDGE_MASK_Y", 240, 0, 640, true);
	panel.addSlider("Radio Interno ", "EDGE_MASK_INNER_RADIUS", 250, 0, 500, true);
	panel.addSlider("Radio Externo ", "EDGE_MASK_OUTER_RADIUS", 350, 0, 600, true);


	if (IM.mode == INPUT_VIDEO) {
		panel.setWhichPanel("Configurar Archivo Video");
		// TODO: add theo's video playing things.... [zach]
	}
	else {
		panel.setWhichPanel("Configurar Video en Vivo");
		panel.addToggle("Cargar config. de Video", "VIDEO_SETTINGS", false);
	}



	panel.loadSettings("settings/trackingSettings.xml");


}

void trackingManager::updateGui() {

	tracker.flip(panel.getValueB("B_RIGHT_FLIP_X"), panel.getValueB("B_RIGHT_FLIP_Y"));

	minBlob = panel.getValueI("MIN_BLOB");
	maxBlob = panel.getValueI("MAX_BLOB");

	threshold = panel.getValueI("THRESHOLD_GAZE");

	tracker.gamma = panel.getValueF("GAMMA");
	tracker.bUseGamma = panel.getValueB("B_USE_GAMMA");

	tracker.contrast = panel.getValueF("CONTRAST");
	tracker.brightness = panel.getValueF("BRIGHTNESS");
	tracker.bUseContrast = panel.getValueB("B_USE_CONTRAST");

	tracker.nDilations = panel.getValueI("N_DILATIONS");
	tracker.bUseDilate = panel.getValueB("B_USE_DILATE");

	int oldx = tracker.edgeMaskStartPos.x;
	int oldy = tracker.edgeMaskStartPos.y;
	int oldir = tracker.edgeMaskInnerRadius;
	int oldor = tracker.edgeMaskOuterRadius;

	tracker.edgeMaskStartPos.x = panel.getValueI("EDGE_MASK_X");
	tracker.edgeMaskStartPos.y = panel.getValueI("EDGE_MASK_Y");
	tracker.edgeMaskInnerRadius = panel.getValueI("EDGE_MASK_INNER_RADIUS");
	tracker.edgeMaskOuterRadius = panel.getValueI("EDGE_MASK_OUTER_RADIUS");

	if (oldx != tracker.edgeMaskStartPos.x ||
		oldy != tracker.edgeMaskStartPos.y ||
		oldir != tracker.edgeMaskInnerRadius ||
		oldor != tracker.edgeMaskOuterRadius) {

		tracker.calculateEdgePixels();

	}

	if (IM.mode != INPUT_VIDEO) {
		panel.setWhichPanel("Configurar Video en Vivo");
		if (panel.getValueB("VIDEO_SETTINGS") == true) {

#ifdef TARGET_OSX
			// since macs fuck up bad fullscreen with video settings
			ofSetFullscreen(false);
#endif
			IM.vidGrabber.videoSettings();
			panel.setValueB("VIDEO_SETTINGS", false);
		}
	}

}

void trackingManager::videoSettings() {


	// TODO: fix this!! [zach]
	//if( !bUseVideoFiles ) ((ofVideoGrabber *)videoSource)->videoSettings();

}

void trackingManager::draw() {

	camara->draw();

	ofSetColor(255, 255, 255);


	//---------------------------------------------------------------- edge
	if (panel.getSelectedPanelName() == "Ajuste de Imagen" || panel.getSelectedPanelName() == "Configurar Video en Vivo") {
		ofSetColor(255, 255, 255);

		tracker.grayImgPreModification.draw(10, 10, 320, 240);
		tracker.grayImg.draw(320 + 20, 10, 320, 240);


		tracker.threshImg.draw(10, 20 + 240, 320, 240);

		ofSetColor(255, 255, 255); //, <#int g#>, <#int b#>)
		ofFill();
		ofRect(320 + 20, 240 + 20, 320, 240);

		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 80);
		tracker.grayImgPreModification.draw(320 + 20, 240 + 20, 320, 240);
		tracker.eyeTrackedEllipse.draw(320 + 20, 240 + 20, 320, 240);

	}

	if (panel.getSelectedPanelName() == "Corrector de Bordes") {
		ofSetColor(255, 255, 255);
		tracker.edgeMaskInverted.draw(10, 10, 320, 240);
		tracker.grayImg.draw(320 + 20, 10, 320, 240);
	}


	if (panel.getSelectedPanelName() == "Detector Blobs") {
		ofSetColor(255, 255, 255);

		tracker.grayImg.draw(10, 10, 320, 240);

		tracker.threshImg.draw(10 + 10 + 320, 10, 320, 240);
		tracker.contourFinder.draw(10 + 10 + 320, 10, 320, 240);
	}

	panel.draw();




}


//--------------------------------------------------------------
void trackingManager::mouseDragged(int x, int y, int button) {

	panel.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void trackingManager::mousePressed(int x, int y, int button) {

	panel.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void trackingManager::mouseReleased() {

	panel.mouseReleased();

}
void trackingManager::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
	cout << "indice " <<e.child << endl;
	IM.vidGrabber.close();
	IM.setup(e.child);
	tracker.setup(IM.width, IM.height);
	minBlob = 10 * 10;
	maxBlob = 100 * 100;
	threshold = 21;

	bFoundEye = false;
	eyePoint.set(0, 0, 0);

}