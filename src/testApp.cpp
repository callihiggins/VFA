#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	ofHideCursor();
    loadSettings("settings.xml");
	receiver.setup( port );	
	box2d.init();
	box2d.setGravity(0, 20);
	box2d.createGround();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	

		polyLine.addVertex(ofGetWidth(), 0);
        polyLine.addVertex(3529, 0);
        polyLine.addVertex(2469, ofGetHeight());
        polyLine.addVertex(1269, ofGetHeight());
        polyLine.addVertex(672, 702);
        polyLine.addVertex(672, 0);
        polyLine.addVertex(0, 0);
	
	// make the shape
	polyLine.setPhysics(0.0, 0.0, 0.3);
	polyLine.create(box2d.getWorld());		
	 backgroundimg.loadImage("images/vimeoarcadeC.png");
}

//--------------------------------------------------------------
void testApp::update() {
	
	
	
	box2d.update();
    
    //OSC STUFF
    while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		if ( m.getAddress() == "/user" )
		{
            uphoto = m.getArgAsString( 0 );
            loaduser = true;
        }
    }
        if(loaduser){
            WinningUser u;
            ofImage * userpic = new ofImage();
            userpic->loadImage(uphoto);
            photos.push_back(userpic);
            u.setPhysics(1.0, 0.0, 0.5);
            u.setup(box2d.getWorld(), 685, 0, 30, 30);
            u.setVelocity(0, 50);
            u.userphoto = userpic;
            winningusers.push_back(u);
            loaduser = false;
        }
	
	
		
}


//--------------------------------------------------------------
void testApp::draw() {
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CORNER);
    backgroundimg.draw(0,0, ofGetWidth(), ofGetHeight());
	

	for(int i=0; i<winningusers.size(); i++) {
		winningusers[i].draw();
	}
	ofSetColor(0, 100, 100);
	polyLine.draw();
	}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
	}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	
	
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
	
}
    
void testApp::loadSettings(string fileString){
        string host_address;
        string filename;
        
        //--------------------------------------------- get configs
        ofxXmlSettings xmlReader;
        bool result = xmlReader.loadFile(fileString);
        if(!result) printf("error loading xml file\n");
        
        
        host_address = xmlReader.getValue("settings:master:address","test",0);
        port = xmlReader.getValue("settings:master:port",5204,0);
        host = (char *) malloc(sizeof(char)*host_address.length());
        strcpy(host, host_address.c_str());

        
        
        int w = xmlReader.getValue("settings:dimensions:width", 640, 0);
        int h = xmlReader.getValue("settings:dimensions:height", 480, 0);
        
        ofSetWindowShape(w, h);
        
        
        if(xmlReader.getValue("settings:go_fullscreen", "false", 0).compare("true") == 0) {
            fullscreen = true;
            ofSetFullscreen(true);
        }
}

