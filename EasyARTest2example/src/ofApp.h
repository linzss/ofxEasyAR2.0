#pragma once

#include "ofMain.h"
#include "ofxEasyAR.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
// key SDK2.0
static std::string key = "WpY2XDSkK3ZAejxAa2XXrr8VrflKzwgxvpFhb3ECYlTYwPiUDfNy0nGW4XPJhuqSDq8n3aQQRQSWq1Q3QA5K0YwQTNyYVz3sCREpW7AsXK6QPRWElPneWMTEqCMe3PdCTY16wauM5eWDvdiw7vh6iWGKUfavqwO0gqRH9NkRtlLFo9ZJUD0T6HAQHxZywrE6csGRBw1F";


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		
		easyar::ofxEasyAR mEasyAR;
		easyar::Vec2I view_size_;

		ofImage mVideoFrame;
		double mLastFrameTimeStamp;

		ofBoxPrimitive mBox;
		ofxAssimpModelLoader mModel;
		ofLight	mLight;

};
