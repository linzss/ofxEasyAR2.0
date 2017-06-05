//
//  ofxEasyAR.h
//  Created by Wei Huan on 7/4/16.
//

#pragma once

#include "ofMain.h"

#include "easyar/frame.hpp"
#include "easyar/image.hpp"
#include "easyar/matrix.hpp"
#include "easyar/vector.hpp"
#include "easyar/camera.hpp"
#include "easyar/player.hpp"
#include "easyar/renderer.hpp"
#include "easyar/engine.hpp"
#include "easyar/framestreamer.hpp"
#include "easyar/qrcode.hpp"

#include "boxrenderer.hpp"
#include "easyar/imagetarget.hpp"
#include "easyar/imagetracker.hpp"

#include <string>
#include <algorithm>

namespace easyar {


class ofxEasyAR
{
public:
	ofxEasyAR() {};
	~ofxEasyAR() {
		stop();
	};

public:
	void setMessageHandler(std::function<void(int, std::string)> func) { message_ = func; }

	bool init(string _key);
	bool start();
	bool stop();

	void render();
	void initGL();
	void resizeGL(int width, int height);
	std::shared_ptr<CameraFrameStreamer> getStreamer() {
		return streamer_;
	}
	std::shared_ptr<CameraDevice> getCamera() {
		return camera_;
	}

	void setQRCode(bool enable);
	void setTrack(bool enable);
	void setHorizontalFlip(bool flip);
private:
	void loadFromImage(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path);
	void loadFromJsonFile(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path, const std::string& targetname);
	void loadAllFromJsonFile(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path);
private:
	std::shared_ptr<CameraDevice> camera_;
	std::shared_ptr<CameraFrameStreamer> streamer_;
	std::shared_ptr<Renderer> renderer_;
	std::shared_ptr<QRCodeScanner> qrcode_;
	std::shared_ptr<ImageTracker> tracker_;

	std::shared_ptr<BoxRenderer> box_renderer_;
	easyar::Vec2I view_size_;
	bool track_enabled_{ true };
	bool qrcode_enabled_{ false };
	std::function<void(int, std::string)> message_;

};

}