

// to change the viewing angle, you'll have to uncomment line 36, 308 and 309.


//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Kevin M. Smith
//  Assignment 3: ImageDragAndDrop
//  This is a simple example of how to drag and drop
//  multiple images into a C++ dynamic array (using the "vector" class)
//
//  I have also illustrated how mouse drag motion could be 
//  applied to rotation of the last loaded image (pivot is the center)
//  when the control-key is held down.
//
//  I have made use of the "EasyCam" class (with 2D rotation disabled)
//  you will need my version of this class which I sent in the 
//  previous example that implementes the "disableRotations()" method.
//
//  I have setup this class so you can pan/zoom the view of your
//  worksspace using the ALT middle mouse and scroll wheel, emulating
//  the way Maya does it.
// 
//  Have Fun !!


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	npts = 0;
	gui.setup();
	gui.add(rotate.setup("Rotate", false));
	gui.add(translate.setup("Translate", false));
	gui.add(scale.setup("Scale", false));
	gui.add(render.setup("Render, press r key to stop", false));
	gui.add(line.setup("Line", false));
	gui.add(view.setup("Change viewing angle", false));
	gui.add(del.setup("Delete"));
	gui.add(clear.setup("Clear"));
	gui.add(save.setup("Save"));
	back.setup("","",800,0);
	back.add(red.setup("Red slider", 0, 0, 255));
	back.add(green.setup("Green slider", 0, 0, 255));
	back.add(blue.setup("Blue slider", 0, 0, 255));
	ofSetVerticalSync(true);
	//ofEnableDepthTest();
	play.addListener(this, &ofApp::playpress);
	stop.addListener(this, &ofApp::stoppress);
	sgui.setup("", "", 400, 0);
	sgui.add(play.setup("play"));
	sgui.add(stop.setup("stop"));
	sgui.add(vol.setup("Volume", 1.0, 0.0, 1.0));
	sample.loadSound("sound.mp3");
	sample.setLoop(true);
	ofEnableAlphaBlending();
	d.load("del.mp3");
	s.load("save.mp3");
	rotx = roty = rotz = 0;
	g.setup("", "", 0, 500);
	g.add(rx.set("x",0.0,0.0,2.0));
	g.add(ry.set("y", 0.0, 0.0, 2.0));
	g.add(rz.set("z",  0.0, 0.0, 2.0));

	// this sets the camera's distance from the object
	cam.setDistance(3000);
	cam.disableMouseInput();
	//cam.disableRotation();
	del.addListener(this, &ofApp::deletepressed);
	clear.addListener(this, &ofApp:: clearpressed);
	save.addListener(this, &ofApp::savepressed);
	//cam.setFarClip(-100);

	//
	// set when <control> key is held down
	//
	//ctrlKeyDown = false;

	// from Image Slection

	//	ofEnableDepthTest(); // commented in Image selection
	//
	// set when <control> key is held down
	//
	selectedImage = NULL;
}

//--------------------------------------------------------------
void ofApp::update() {
	rotx = rotx + rx;
	roty = roty + ry;
	rotz = rotz + rz;
}
void ofApp::playpress() {
	sample.play();
}

void ofApp::stoppress() {
	sample.stop();
}


void ofApp::clearpressed() {
	line1.clear();
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	ofBackground(red,green,blue,0);
	ofFill();
	
	//
	// go through our list of images to draw
	//
	/*for (int i = images.size()-1; i >= 0; i--)
	images[i]->draw();
	cam.end();*/

	// from Image Selection

	

	line1.draw();

	for (int i = 0; i < images.size(); i++) {
		images[i]->draw();
	}
	cam.end();
	gui.draw();
	back.draw();
	sgui.draw();
	g.draw();
	ofSetColor(255,0,0);
	ofRotateX(rotx);
	ofRotateY(roty);
	ofRotateZ(rotz);
	ofCircle(900, 500, 30);
	ofCircle(950, 550, 30);
	sample.setVolume(vol);
}

//
// delete all images in list on exit
//
void ofApp::exit() {
	for (int i = 0; i < images.size(); i++) {
		delete images[i];
	}

}


void ofApp::keyPressed(int key) {
	
	switch (key) {
	case 'C':
	case 'c':
		if (cam.getMouseInputEnabled()) cam.disableMouseInput();
		else cam.enableMouseInput();
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'r':
		doRendering();
		break;

	
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case 'r':
		undorendering();
	default:
		break;
	}
	
}
	

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (ctrlKeyDown) doMouseRotation(x, y); //From Image drag and drop
	if (shiftkeydown) doTranslation(x, y);
	if (tabkeydown) doScaling(x, y);
	if (linedown)
	{
		ofPoint pt;
		pt.set(x-1050, (-y+500));
		line1.addVertex(pt);
	}
}

void ofApp::doRendering()
{
	ofEnableDepthTest();
}

void ofApp::undorendering()
{
	ofDisableDepthTest();
}
//
// This is just a simple example of how you could apply mouse 
// motion to rotation. In this example, there is no selection 
// implemented

//, so we apply rotations to last image loaded.
//



void ofApp::doTranslation(int x, int y) {
	
	
		tabkeydown = false;
		ctrlKeyDown = false;

	//This method is from image drag and drop

	// if there are no images stored in the list, just return
	//
	if (images.size() == 0) return;

	float rotation;
	ofVec2f mouse = ofVec2f(x, y);
	int x1 =(int) mouse.x - lastMouse.x;
	int y1 = (int)(mouse.y - lastMouse.y)*-1;
	//float dist = delta.length();
	
	// if mouse is moving from left to right, apply positive rotation
	// otherwise apply negative rotation.
	// 
	//if (mouse.x < lastMouse.x)
		//rotation = -dist;
	//else
	//	rotation = dist;
		
	// store value of where the mouse was last for next entry
	// 
	lastMouse = mouse;

	// apply rotation to image (will be rotated to this value on next redraw)
	//
	//images[images.size() - 1]->rot += rotation;
	images[images.size() - 1]->trans.x += x1;
	images[images.size() - 1]->trans.y += y1;
	
}


void ofApp::doScaling(int x, int y) {
	

		shiftkeydown = false;
		ctrlKeyDown = false;
	//[[NSCursor pointingHandCursor] set];

	//This method is from image drag and drop

	// if there are no images stored in the list, just return
	//
	/*if (images.size() == 0) return;

	float rotation;
	ofVec2f mouse = ofVec2f(x, y);
	float x1 = (float)mouse.x /512;
	float y1 = (float)mouse.y/384;
	cout << "\n\n",x1,y1;
	//float dist = delta.length();

	// if mouse is moving from left to right, apply positive rotation
	// otherwise apply negative rotation.
	// 
	//if (mouse.x < lastMouse.x)
	//rotation = -dist;
	//else
	//	rotation = dist;

	// store value of where the mouse was last for next entry
	// 
	lastMouse = mouse;

	// apply rotation to image (will be rotated to this value on next redraw)
	//
	//images[images.size() - 1]->rot += rotation;
	images[images.size() - 1]->scale.x = x1;
	images[images.size() - 1]->scale.y = y1;
	*/

	////////////////////////////////////////////////////////////////////////////////////////
	if (images.size() == 0) return;

	float rotation;
	ofVec2f mouse = ofVec2f(x, y);
	ofVec2f delta = mouse - lastMouse;
	float dist = delta.length();

	// if mouse is moving from left to right, apply positive rotation
	// otherwise apply negative rotation.
	// 
	if (mouse.x < lastMouse.x)
		rotation = -dist;
	else
		rotation = dist;

	// store value of where the mouse was last for next entry
	// 
	lastMouse = mouse;

	// apply rotation to image (will be rotated to this value on next redraw)
	//
	images[images.size() - 1]->scale += rotation/100;

	
	/////////////////////////////////////////////////////////////////////////////////////////


}




void ofApp::doMouseRotation(int x, int y) {
		shiftkeydown = false;
	
		tabkeydown = false;
	//This method is from image drag and drop

	// if there are no images stored in the list, just return
	//
	if (images.size() == 0) return;

	float rotation;
	ofVec2f mouse = ofVec2f(x, y);
	ofVec2f delta = mouse - lastMouse;
	float dist = delta.length();

	// if mouse is moving from left to right, apply positive rotation
	// otherwise apply negative rotation.
	// 
	if (mouse.x < lastMouse.x)
		rotation = -dist;
	else
		rotation = dist;

	// store value of where the mouse was last for next entry
	// 
	lastMouse = mouse;

	// apply rotation to image (will be rotated to this value on next redraw)
	//
	images[images.size() - 1]->rot += rotation;
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

		if (translate == true)
			shiftkeydown = true;
		else
			shiftkeydown = false;
		if (scale == true)
			tabkeydown = true;
		else
			tabkeydown = false;
		if (rotate == true)
			ctrlKeyDown = true;
		else
			ctrlKeyDown = false;
		if (render == true)
		{
			rkey = true; doRendering();
		}
		else
		{
			rkey = false;
			undorendering();
		}
		if (line == true)
			linedown = true;
		else
			linedown = false;
		if (view == true)
			cam.enableMouseInput();
		else
			cam.disableMouseInput();
		if (clear == true)
			npts = 0;
		if (save == true)
		{
			img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			img.save("zoomzoom.png");
		}

	lastMouse = ofVec2f(x, y);

	//From image selection

	renderSelection();
	processSelection(x, y);
}
void ofApp::deletepressed()
{
	delete_the_image();
	d.play();
}
void ofApp::savepressed()
{
	
	//img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	//img.save("zoomzoom.png");
	ofFileDialogResult res;
	res = ofSystemSaveDialog("preset.xml", "Saving Preset");
	if (res.bSuccess)
		cout << "res: " << res.filePath << endl;
	img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	//img.save(res.filePath+".png");
	img.save(res.filePath + ".jpg");
	ofSaveScreen(res.filePath + ".png");
	s.play();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::delete_the_image()
{
	cout << "deleting";
	for (int i = 0; i < images.size(); i++) {
		if (images[i] == selectedImage) {
			images.erase(images.begin() + i);
		}
	}
}

//--------------------------------------------------------------
//
// Simple file drag and drop implementation.
void ofApp::dragEvent(ofDragInfo dragInfo) {

	Image *imageObj = new Image();
	imageObj->trans = cam.screenToWorld(dragInfo.position);
	if (imageObj->image.load(dragInfo.files[0]) == true)
		images.push_back(imageObj);
	else {
		cout << "Can't load image: " << dragInfo.files[0] << endl;
		delete imageObj;
	}
}

//From image selection


void ofApp::renderSelection() {
	cam.begin();
	ofBackground(0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (int i = 0; i < images.size(); i++) {
		images[i]->draw(true, i);
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	cam.end();
}


void ofApp::processSelection(int x, int y) {
	unsigned char res[4];
	GLint viewport[4];

	// read pixel under mouse x y
	//
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

	if (selectedImage) {
		selectedImage->bSelected = false;
		selectedImage = NULL;
	}

	//
	//  lookup image by color of pixel
	//
	if (res[0] > 0 && res[0] <= images.size()) {
		Image *image = images[res[0] - 1];
		image->bSelected = true;
		selectedImage = image;

		// move selected image to beginning of list
		//
		images.erase(images.begin() + (res[0] - 1));
		images.push_back(image);
	}

}

Image::Image()
{
	trans.x = 0;
	trans.y = 0;
	scale.x = 1.0;
	scale.y = 1.0;
	rot = 0;
	//from Image Selection
	bSelected = false;
}



void Image::draw(bool bSelectMode, int index) {
	ofPushMatrix();
	ofTranslate(trans.x,trans.y);
	ofScale(scale);
	ofRotate(rot);

	//
	// if drawing image normally
	//
	if (!bSelectMode) {

		//
		// if selected, draw a light yellowo box around image
		//
		if (bSelected) {
			ofNoFill();
			ofSetColor(255, 255, 0);
			ofSetLineWidth(2);
			ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
				image.getWidth(), image.getHeight());
		}
		ofSetColor(255, 255, 255, 255);
		image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);

	}
	//
	// else if drawing to test selection
	//
	else {
		ofFill();
		ofSetColor(index + 1, 0, 0);
		ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
			image.getWidth(), image.getHeight());
	}
	ofPopMatrix();
}
