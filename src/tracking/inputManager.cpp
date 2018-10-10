#include "inputManager.h"

/*
<app>

<!-- mode, input 0 = live, 1 = video -->
<mode>1</mode>

<!-- some per mode settings -->
<videoFile>inputTestVideos/test1.mov</videoFile>

<videoGrabber>
<width>640</width>
<height>480</height>

<!-- this is optional -->
<deviceId></deviceId>
</videoGrabber>


</app>
*/

//--------------------------------------------------------------
void inputManager::setup(int camara) {

	ofxXmlSettings XML;
	XML.loadFile("settings/inputSettings.xml");
	mode = XML.getValue("app:mode", 0);

	if (mode == INPUT_VIDEO) {
		//cout << "input manager: loading video file" << endl;
		string movieToLoad = XML.getValue("app:videoFile", "");
		vidPlayer.loadMovie(movieToLoad);
		vidPlayer.play();
		width = vidPlayer.getWidth();
		height = vidPlayer.getHeight();
	}

	if (mode == INPUT_LIVE_VIDEO) {
		
		width = XML.getValue("app:videoGrabber:width", 640);
		height = XML.getValue("app:videoGrabber:height", 480);
		int device = XML.getValue("app:videoGrabber:deviceId", 0);

		if (device != 0) {
			vidGrabber.setDeviceID(camara);
		}

		vidGrabber.initGrabber(width, height, false);	// false = no texture. faster...
		width = vidGrabber.getWidth();
		height = vidGrabber.getHeight();		// in case we are different then what we request... ;)
	}

	if (width != 0 || height != 0) {
		colorImg.setUseTexture(false);
		grayImage.setUseTexture(false);
		colorImg.allocate(width, height);
		grayImage.allocate(width, height);
	}

	bIsFrameNew = false;

}

//--------------------------------------------------------------
void inputManager::update() {



	if (mode == INPUT_LIVE_VIDEO) {
		vidGrabber.update();
		bIsFrameNew = vidGrabber.isFrameNew();
	}
	else {
		vidPlayer.update();
		bIsFrameNew = vidPlayer.isFrameNew();
	}

	if (bIsFrameNew) {

		if (mode == INPUT_LIVE_VIDEO) {
			colorImg.setFromPixels(vidGrabber.getPixels().getData(), width, height);
		}
		else {
			colorImg.setFromPixels(vidPlayer.getPixels().getData(), width, height);
		}

		grayImage = colorImg;		// TODO: this color to gray conversion is *slow*, since it's using the CV cvt color, we can make this faster !

	}
}