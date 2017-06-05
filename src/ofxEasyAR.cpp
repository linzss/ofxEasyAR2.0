

#include "ofxEasyAR.h"


namespace easyar {

	void ofxEasyAR::loadFromImage(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path)
	{
		auto target = std::make_shared<easyar::ImageTarget>();
		std::string jstr = "{\n"
			"  \"images\" :\n"
			"  [\n"
			"    {\n"
			"      \"image\" : \"" + path + "\",\n"
			"      \"name\" : \"" + path.substr(0, path.find_first_of(".")) + "\"\n"
			"    }\n"
			"  ]\n"
			"}";
		target->setup(jstr.c_str(), static_cast<int>(easyar::StorageType::Assets) | static_cast<int>(easyar::StorageType::Json), "");
		tracker->loadTarget(target, [this](std::shared_ptr<easyar::Target> target, bool status) {
			if (!message_)
				return;
			message_(status, "load target (" + std::to_string(status) + "): " + target->name() + " (" + std::to_string(target->runtimeID()) + ")");
		});
	}

	void ofxEasyAR::loadFromJsonFile(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path, const std::string& targetname)
	{
		auto target = std::make_shared<easyar::ImageTarget>();
		target->setup(path, static_cast<int>(easyar::StorageType::Assets), targetname);
		tracker->loadTarget(target, [this](std::shared_ptr<easyar::Target> target, bool status) {
			if (!message_)
				return;
			message_(status, "load target (" + std::to_string(status) + "): " + target->name() + " (" + std::to_string(target->runtimeID()) + ")");
		});
	}

	void ofxEasyAR::loadAllFromJsonFile(std::shared_ptr<easyar::ImageTracker> tracker, const std::string& path)
	{
		for (auto && target : easyar::ImageTarget::setupAll(path, static_cast<int>(easyar::StorageType::Assets))) {
			tracker->loadTarget(target, [this](std::shared_ptr<easyar::Target> target, bool status) {
				if (!message_)
					return;
				message_(status, "load target (" + std::to_string(status) + "): " + target->name() + " (" + std::to_string(target->runtimeID()) + ")");
			});
		}
	}

	bool ofxEasyAR::init(string _key)
	{		
		auto result = Engine::initialize(_key);
		if (!result) {
			std::printf("initialization failed\n");
			return 1;
		}
		camera_ = std::make_shared<CameraDevice>();
		streamer_ = std::make_shared<CameraFrameStreamer>();
		streamer_->attachCamera(camera_);

		qrcode_ = std::make_shared<QRCodeScanner>();
		qrcode_->attachStreamer(streamer_);

		tracker_ = std::make_shared<ImageTracker>();
		tracker_->attachStreamer(streamer_);

		bool status = true;
		status &= camera_->open(static_cast<int>(CameraDeviceType::Default));
		camera_->setSize({ { 1280, 720 } });

		loadFromJsonFile(tracker_, "data/targets.json", "argame");
		loadFromJsonFile(tracker_, "data/targets.json", "idback");
		loadAllFromJsonFile(tracker_, "data/targets2.json");
		loadFromImage(tracker_, "data/namecard.jpg");
		return status;
	}

	bool ofxEasyAR::start()
	{
		if (!camera_)
			return false;
		bool status = true;
		status &= camera_->start();
		status &= streamer_->start();
		camera_->setFocusMode(CameraDeviceFocusMode::Continousauto);

		if (qrcode_enabled_)
			status &= qrcode_->start();

		if (track_enabled_)
			status &= tracker_->start();
		return status;
	}

	bool ofxEasyAR::stop()
	{
		if (!camera_)
			return false;
		bool status = true;
		status &= tracker_->stop();
		status &= qrcode_->stop();
		status &= streamer_->stop();
		status &= camera_->stop();
		return status;
	}

	void ofxEasyAR::setTrack(bool enable)
	{
		track_enabled_ = enable;
		if (!tracker_)
			return;
		if (track_enabled_)
			tracker_->start();
		else
			tracker_->stop();
	}

	void ofxEasyAR::setQRCode(bool enable)
	{
		qrcode_enabled_ = enable;
		if (!qrcode_)
			return;
		if (qrcode_enabled_)
			qrcode_->start();
		else
			qrcode_->stop();
	}

	void ofxEasyAR::setHorizontalFlip(bool flip)
	{
		if (!camera_)
			return;
		camera_->setHorizontalFlip(flip);
	}

	void ofxEasyAR::initGL()
	{
		if (renderer_)
			return;
		renderer_ = std::make_shared<Renderer>();
		box_renderer_ = std::make_shared<BoxRenderer>();
		box_renderer_->init();
	}

	void ofxEasyAR::render()
	{
		initGL();
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Vec4I viewport;
		auto frame = streamer_->peek();
		if (camera_ && camera_->isOpened()) {
			Vec2I p;
			Vec2I size = camera_->size();
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
		glViewport(viewport.data[0], viewport.data[1], viewport.data[2], viewport.data[3]);
		renderer_->render(frame, viewport);

		for (auto && target : frame->targetInstances()) {
			if (target->status() == TargetStatus::Tracked) {
				auto imagetarget = std::dynamic_pointer_cast<ImageTarget>(target->target());
				if (!imagetarget)
					continue;
				box_renderer_->render(camera_->projectionGL(0.2f, 500.f), target->poseGL(), imagetarget->size());
			}
		}

		static int qrcode_index = 0;
		if (frame->index() != qrcode_index) {
			qrcode_index = frame->index();
			if (!frame->text().empty()) {
				if (message_)
					message_(1, "qrcode: " + frame->text());
			}
		}
	}

	void ofxEasyAR::resizeGL(int width, int height)
	{
		view_size_ = { width, height };
	}

}