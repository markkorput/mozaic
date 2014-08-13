#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // UI
    gui = new ofxUISuperCanvas("GRID");
    gui->addSpacer();
    gui->addSlider("GRIDCELLW", 0, 1000, 100.0);
    gui->addSlider("GRIDCELLH", 0, 1000, 100.0);
    gui->addSlider("GRIDOFFSETX", 0, 1000, 0.0);
    gui->addSlider("GRIDOFFSETY", 0, 1000, 0.0);
    gui->addButton("Generate", true);
//    gui->addSpacer();
//    gui->addLabel("CIRCLE CONTROL");
//    gui->addSlider("RED", 0.0, 255.0, red);
//	gui->addSlider("GREEN", 0.0, 255.0, green);
//    gui->addSlider("BLUE", 0.0, 255.0, blue);
//    gui->addSlider("ALPHA", 0.0, 255.0, alpha);
//    gui->addSlider("RADIUS", 0.0, 600.0, radius);
//	gui->addSlider("RESOLUTION", 3, 60, resolution);
//    gui->addLabelToggle("DRAW FILL", drawFill);
//    gui->add2DPad("POSITION", ofPoint(0, ofGetWidth()), ofPoint(0, ofGetHeight()), position);
//    gui->addSpacer();
//    gui->addTextArea("TEXT AREA", "HIDE & SHOW GUI BY PRESSING 'g'. MOUSE OVER A SLIDER AND PRESS UP, DOWN, LEFT, RIGHT", OFX_UI_FONT_SMALL);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    gui->loadSettings("guiSettings.xml");

    // IMAGE
    image = NULL;
    
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    fbo.begin();
        ofBackground(0,0,0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    fbo.draw(0,0);

    
    // draw grid
    int x = (int)((ofxUISlider *)gui->getWidget("GRIDOFFSETX"))->getScaledValue();
    int y = (int)((ofxUISlider *)gui->getWidget("GRIDOFFSETY"))->getScaledValue();
    int w = (int)((ofxUISlider *)gui->getWidget("GRIDCELLW"))->getScaledValue();
    int h = (int)((ofxUISlider *)gui->getWidget("GRIDCELLH"))->getScaledValue();
    if(w < 1) w = 1;
    if(h < 1) h = 1;
    ofLogVerbose() << "(Grid: x,y,w,h) - " << x << "," << y << "," << w << "," << h;

    for(x *= -1; x<ofGetWindowWidth(); x+=w) ofLine(x, 0, x, ofGetWindowHeight());
    for(y *= -1; y<ofGetWindowHeight(); y+=h) ofLine(0, y, ofGetWindowWidth(), y);
}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("guiSettings.xml");
    delete gui;
    delete image;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    // ofLogNotice("dragEvent") << dragInfo.files[0];
    // unload existing image
    ofLogVerbose("UNloading existing image");
    delete image;

    // load image
    ofLogVerbose("Loading new image");
    image = new ofImage(dragInfo.files[0]);
    ofSetWindowShape(image->getWidth(), image->getHeight());
    fbo.allocate(image->getWidth(), image->getHeight());
    
    fbo.begin();
        image->draw(0, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "Generate"){
        int uix = (int)((ofxUISlider *)gui->getWidget("GRIDOFFSETX"))->getScaledValue();
        int y = (int)((ofxUISlider *)gui->getWidget("GRIDOFFSETY"))->getScaledValue();
        int w = (int)((ofxUISlider *)gui->getWidget("GRIDCELLW"))->getScaledValue();
        int h = (int)((ofxUISlider *)gui->getWidget("GRIDCELLH"))->getScaledValue();
        if(w < 1) w = 1;
        if(h < 1) h = 1;

        fbo.begin();
            for(y *= -1; y<ofGetWindowHeight(); y+=h)
            for(int x = uix * -1; x<ofGetWindowWidth(); x+=w)
                image->drawSubsection(x, y, w, h, (int)ofRandom(image->getWidth()-w), ofRandom(image->getHeight()-h));
        fbo.end();
    }
        
	/* string name = e.widget->getName();
	int kind = e.widget->getKind();
	
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		red = slider->getScaledValue();
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		green = slider->getScaledValue();
	}
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		blue = slider->getScaledValue();
	}
	else if(name == "BGR")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.r = rslider->getScaledValue();
	}
	else if(name == "BGG")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.g = rslider->getScaledValue();
	}
	else if(name == "BGB")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget;
		backgroundColor.b = rslider->getScaledValue();
	}
	else if(name == "ALPHA")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		alpha = slider->getScaledValue();
	}
	else if(name == "RADIUS")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		radius = slider->getScaledValue();
	}
	else if(name == "RESOLUTION")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		resolution = slider->getScaledValue();          //gets the value from the specified range, otherwise you can get a normalized value (0.0 -> 1.0);
        ofSetCircleResolution(resolution);
        slider->setValue(resolution);                   //shows the int value on the slider
	}
    else if(name == "POSITION")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget;
		position.x = pad->getPercentValue().x*ofGetWidth();
		position.y = pad->getPercentValue().y*ofGetHeight();
	}
    else if(name == "DRAW FILL")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        drawFill = toggle->getValue();
    } */
}