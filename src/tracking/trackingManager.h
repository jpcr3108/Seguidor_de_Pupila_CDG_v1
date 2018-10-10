#pragma once
#define _TRACKSCENE_H



#include "ofMain.h"
#include "eyeTracker.h"
#include "ofxControlPanel.h"
#include "inputManager.h"
#include "ofxDatGui.h"


class trackingManager {

public:
	
	void setup();
	void update();
	void draw();

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();

	void onDropdownEvent(ofxDatGuiDropdownEvent e);

	void setupGui();
	void updateGui();

	void trackEyes();

	// open video settings panel if using a camera
	void videoSettings();

	// returns the tracked pupil centroid
	ofPoint	getEyePoint();
	bool	bGotAnEyeThisFrame();


	ofxControlPanel		panel;

	ofxDatGuiDropdown* camara;

	//----- video sources... what are we tracking!

	inputManager		IM;

	eyeTracker			tracker;

	int					minBlob, maxBlob;
	float				threshold;
	bool				bFoundEye;
	ofPoint				eyePoint;


};