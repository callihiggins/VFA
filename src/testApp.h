#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

// ------------------------------------------------- a simple extended box2d circle

class WinningUser : public ofxBox2dRect {
	
public:
	
    
    ofImage * userphoto;  
	
      void draw() {
		float width = getWidth()*2;
        float height = getHeight()*2;
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
        ofRotateZ(getRotation());
		ofSetColor(255);
        userphoto->draw(0,0,width, height);
		glPopMatrix();
		
	}
};


// -------------------------------------------------
class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
    void loadSettings(string fileString);
	
	float							px, py;
	bool							bDrawLines;
	bool							loaduser, fullscreen;
    ofImage                         backgroundimg;
    vector		<ofImage*>          photos;
    vector      <WinningUser>       winningusers;
    string                          uphoto;
    ofxBox2d						box2d;			  //	the box2d world
    ofxOscReceiver                  receiver;
    ofPolyline						drawing;		  //	we draw with this first
	ofxBox2dPolygon					polyLine;		  //	the box2d polygon/line shape
	int                             port;
    char * host;
};
