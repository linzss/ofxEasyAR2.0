#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//ofLog() << "begin setup" << std::endl;

	//ofSetFrameRate(30);

	mModel.loadModel("dwarf.x", true);
	mModel.setScale(0.02f, 0.02f, 0.02f);
	mModel.setRotation(0, 90, 1.0f, 0.0f, 0.0f);
	mModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	mModel.playAllAnimations();


	mEasyAR.init(key);
	mEasyAR.start();

	/*mEasyAR.setup(key);
	mEasyAR.initCamera();
	mEasyAR.loadFromJsonFile("data/targets.json", "argame");
	mEasyAR.loadFromJsonFile("data/targets.json", "idback");
	mEasyAR.loadAllFromJsonFile("data/targets2.json");
	mEasyAR.loadFromImage("data/namecard.jpg");
	mEasyAR.start();*/

	ofSleepMillis(1000);

	mLastFrameTimeStamp = 0.0;
	view_size_ = { ofGetWidth(), ofGetHeight() };
}

//--------------------------------------------------------------
void ofApp::update(){

	mModel.update();

	//mEasyAR.nextFrame();

	std::shared_ptr<easyar::Frame> _frame = mEasyAR.getStreamer()->peek();
	std::shared_ptr<easyar::Image> _image = _frame->images()[0];
	//cout << _frame->images().size() << endl;

	if (mLastFrameTimeStamp != _frame->timestamp())
	{
		ofPixels _p;
		_p.setFromExternalPixels((unsigned char*)_image->data(), _image->width(), _image->height(), OF_PIXELS_BGR);
		_p.swapRgb();
		mVideoFrame.setFromPixels(_p);
		mLastFrameTimeStamp = _frame->timestamp();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	mVideoFrame.draw(0, 0);
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, 15);


	easyar::Vec4I viewport;
	auto frame = mEasyAR.getStreamer()->peek();
	/**/if (mEasyAR.getCamera() && mEasyAR.getCamera()->isOpened()) {
		easyar::Vec2I p;
		easyar::Vec2I size = mEasyAR.getCamera()->size();
		if (view_size_.data[0] / (float)size.data[0] < view_size_.data[1] / (float)size.data[1]) {
			p.data[0] = 0;
			p.data[1] = (int)(view_size_.data[1] - view_size_.data[0] / (float)size.data[0] * (float)size.data[1]) / 2;
		}
		else {
			p.data[0] = (int)(view_size_.data[0] - view_size_.data[1] / (float)size.data[1] * (float)size.data[0]) / 2;
			p.data[1] = 0;
		}
		viewport = { { p.data[0], p.data[1], view_size_.data[0] - p.data[0] * 2, view_size_.data[1] - p.data[1] * 2 } };
	}
	else if (view_size_.data[0] > 0) {
		viewport = { { 0, 0, view_size_.data[0], view_size_.data[1] } };
	}
	//glViewport(viewport.data[0], viewport.data[1], viewport.data[2], viewport.data[3]);
	//renderer_->render(frame, viewport);
	cout << frame->targetInstances().size() << endl;
	for (auto && target : frame->targetInstances()) {
		if (target->status() == easyar::TargetStatus::Tracked) {
			/*auto imagetarget = std::dynamic_pointer_cast<easyar::ImageTarget>(target->target());
			if (!imagetarget)
				continue;*/
			easyar::Matrix44F projectionMatrix = mEasyAR.getCamera()->projectionGL(0.2f, 500.f);
			easyar::Matrix44F cameraview = target->poseGL();
			//easyar::ImageTarget target = _frame.targets()[0].target().cast_dynamic<EasyAR::ImageTarget>();

			ofEnableBlendMode(OF_BLENDMODE_ALPHA);

			ofEnableDepthTest();
#ifndef TARGET_PROGRAMMABLE_GL    
			glShadeModel(GL_SMOOTH); //some model / light stuff
#endif
			mLight.enable();
			ofEnableSeparateSpecularLight();

			ofPushMatrix();

			//glViewport(0, 0, 640, 480);
			glViewport(viewport.data[0], viewport.data[1], viewport.data[2], viewport.data[3]);
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(&projectionMatrix.data[0]);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(&cameraview.data[0]);

			//mBox.setScale(0.02f);
			//mBox.draw();

			mModel.drawFaces();
			ofPopMatrix();

			ofDisableDepthTest();
			mLight.disable();
			ofDisableLighting();
			ofDisableSeparateSpecularLight();
		}
	}
	
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
