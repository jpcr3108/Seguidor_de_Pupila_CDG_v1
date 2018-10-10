#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include <wtypes.h>
int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

//========================================================================
int main( ){
	
	ofAppGlutWindow window;
	cout << w << " " << h << "\n";
	ofSetupOpenGL(w,h,OF_WINDOW);	
	ofToggleFullscreen();// <-------- setup the GL context
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREENfff
	// pass in width and height too:
	ofRunApp(new ofApp());	
}
