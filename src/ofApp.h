#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class Image {

public:
	Image();
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	ofImage image;
	//void	draw();

	// from image selection

	void	draw(bool bSelectMode = false, int index = 0);
};



class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void renderSelection();
	void processSelection(int x, int y);
	void delete_the_image();
	void tra();
	void doMouseRotation(int x, int y);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void doTranslation(int x, int y);
	void doScaling(int x, int y);
	void doRendering();
	ofImage img;
	ofImage ima;
private:
	//ofEasyCam	cam;
	ofVec2f		lastMouse;
	bool		ctrlKeyDown;
	bool shiftkeydown, tabkeydown;
	bool rkey;

	//vector<Image *> images;

	// from image selection

	ofEasyCam	cam;
	vector<Image *> images;
	Image *selectedImage;
	/*bool hit_translate = 0;
	ofRectangle button_translate;
	bool hit_scale = 0;
	ofRectangle button_scale;
	bool hit_delete = 0;
	ofRectangle button_delete;
	bool hit_save = 0;
	ofRectangle button_save;
	bool hit_rotate = 0;
	ofRectangle button_rotate;
	bool hit_view = 0;
	ofRectangle button_view;*/
public:
	ofParameter<float> rx, ry, rz;
	void deletepressed();
	void clearpressed();
	void savepressed();
	ofxPanel gui;
	ofxPanel g;
	ofxToggle translate;
	ofxToggle render;
	void undorendering();
	ofxToggle scale;
	ofxToggle rotate;
	ofxToggle view;
	ofxButton del;
	ofxButton save;
	void playpress();
	void stoppress();
	ofxPanel back;
	ofxIntSlider red;
	ofxIntSlider green;
	ofxIntSlider blue;
	ofSoundPlayer d;
	ofSoundPlayer s;
	ofxPanel sgui;
	ofxButton play;
	ofxButton stop;
	ofxButton clear;
	ofxFloatSlider vol;
	ofSoundPlayer sample;
	ofPoint pts[3000];
	int npts;
	void drawline(int,int);
	ofxToggle line;
	ofPolyline line1;
	bool linedown;
	float rotx, roty, rotz;
};