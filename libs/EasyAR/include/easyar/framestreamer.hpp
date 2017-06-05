//=============================================================================================================================
//
// EasyAR 2.0.0
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_FRAMESTREAMER_HPP__
#define __EASYAR_FRAMESTREAMER_HPP__

#include "easyar/types.hpp"

namespace easyar {

class FrameStreamer
{
protected:
    std::shared_ptr<easyar_FrameStreamer> cdata_;
    void init_cdata(std::shared_ptr<easyar_FrameStreamer> cdata);
    FrameStreamer & operator=(const FrameStreamer & data) = delete;
public:
    FrameStreamer(std::shared_ptr<easyar_FrameStreamer> cdata);
    virtual ~FrameStreamer();

    std::shared_ptr<easyar_FrameStreamer> get_cdata();

    std::shared_ptr<Frame> peek();
    bool start();
    bool stop();
};

class CameraFrameStreamer : public FrameStreamer
{
protected:
    std::shared_ptr<easyar_CameraFrameStreamer> cdata_;
    void init_cdata(std::shared_ptr<easyar_CameraFrameStreamer> cdata);
    CameraFrameStreamer & operator=(const CameraFrameStreamer & data) = delete;
public:
    CameraFrameStreamer(std::shared_ptr<easyar_CameraFrameStreamer> cdata);
    virtual ~CameraFrameStreamer();

    std::shared_ptr<easyar_CameraFrameStreamer> get_cdata();

    CameraFrameStreamer();
    std::string typeName();
    bool attachCamera(std::shared_ptr<CameraDevice> obj);
    std::shared_ptr<Frame> peek();
    bool start();
    bool stop();
    static std::shared_ptr<CameraFrameStreamer> tryCastFromFrameStreamer(std::shared_ptr<FrameStreamer> v);
};

}

namespace std {

template<>
inline shared_ptr<easyar::CameraFrameStreamer> dynamic_pointer_cast<easyar::CameraFrameStreamer, easyar::FrameStreamer>(const shared_ptr<easyar::FrameStreamer> & r) noexcept
{
    return easyar::CameraFrameStreamer::tryCastFromFrameStreamer(r);
}

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_FRAMESTREAMER_HPP__
#define __IMPLEMENTATION_EASYAR_FRAMESTREAMER_HPP__

#include "easyar/framestreamer.h"
#include "easyar/frame.hpp"
#include "easyar/camera.hpp"

namespace easyar {

inline FrameStreamer::FrameStreamer(std::shared_ptr<easyar_FrameStreamer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
inline FrameStreamer::~FrameStreamer()
{
    cdata_ = nullptr;
}

inline std::shared_ptr<easyar_FrameStreamer> FrameStreamer::get_cdata()
{
    return cdata_;
}
inline void FrameStreamer::init_cdata(std::shared_ptr<easyar_FrameStreamer> cdata)
{
    cdata_ = cdata;
}
inline std::shared_ptr<Frame> FrameStreamer::peek()
{
    easyar_Frame * _return_value_;
    easyar_clearException();
    easyar_FrameStreamer_peek(cdata_.get(), &_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return (_return_value_ == nullptr ? nullptr : std::make_shared<Frame>(std::shared_ptr<easyar_Frame>(_return_value_, [](easyar_Frame * ptr) { easyar_Frame__dtor(ptr); })));
}
inline bool FrameStreamer::start()
{
    easyar_clearException();
    auto _return_value_ = easyar_FrameStreamer_start(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline bool FrameStreamer::stop()
{
    easyar_clearException();
    auto _return_value_ = easyar_FrameStreamer_stop(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}

inline CameraFrameStreamer::CameraFrameStreamer(std::shared_ptr<easyar_CameraFrameStreamer> cdata)
    :
    FrameStreamer(std::shared_ptr<easyar_FrameStreamer>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
inline CameraFrameStreamer::~CameraFrameStreamer()
{
    cdata_ = nullptr;
}

inline std::shared_ptr<easyar_CameraFrameStreamer> CameraFrameStreamer::get_cdata()
{
    return cdata_;
}
inline void CameraFrameStreamer::init_cdata(std::shared_ptr<easyar_CameraFrameStreamer> cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameStreamer * ptr = nullptr;
        easyar_castCameraFrameStreamerToFrameStreamer(cdata_.get(), &ptr);
        FrameStreamer::init_cdata(std::shared_ptr<easyar_FrameStreamer>(ptr, [](easyar_FrameStreamer * ptr) { easyar_FrameStreamer__dtor(ptr); }));
    }
}
inline CameraFrameStreamer::CameraFrameStreamer()
    :
    FrameStreamer(std::shared_ptr<easyar_FrameStreamer>(nullptr)),
    cdata_(nullptr)
{
    easyar_CameraFrameStreamer * _return_value_;
    easyar_clearException();
    easyar_CameraFrameStreamer__ctor(&_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    init_cdata(std::shared_ptr<easyar_CameraFrameStreamer>(_return_value_, [](easyar_CameraFrameStreamer * ptr) { easyar_CameraFrameStreamer__dtor(ptr); }));
}
inline std::string CameraFrameStreamer::typeName()
{
    easyar_String * _return_value_;
    easyar_clearException();
    easyar_CameraFrameStreamer_typeName(cdata_.get(), &_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
inline bool CameraFrameStreamer::attachCamera(std::shared_ptr<CameraDevice> arg0)
{
    easyar_clearException();
    auto _return_value_ = easyar_CameraFrameStreamer_attachCamera(cdata_.get(), (arg0 == nullptr ? nullptr : arg0->get_cdata().get()));
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline std::shared_ptr<Frame> CameraFrameStreamer::peek()
{
    easyar_Frame * _return_value_;
    easyar_clearException();
    easyar_CameraFrameStreamer_peek(cdata_.get(), &_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return (_return_value_ == nullptr ? nullptr : std::make_shared<Frame>(std::shared_ptr<easyar_Frame>(_return_value_, [](easyar_Frame * ptr) { easyar_Frame__dtor(ptr); })));
}
inline bool CameraFrameStreamer::start()
{
    easyar_clearException();
    auto _return_value_ = easyar_CameraFrameStreamer_start(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline bool CameraFrameStreamer::stop()
{
    easyar_clearException();
    auto _return_value_ = easyar_CameraFrameStreamer_stop(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline std::shared_ptr<CameraFrameStreamer> CameraFrameStreamer::tryCastFromFrameStreamer(std::shared_ptr<FrameStreamer> v)
{
    if (v == nullptr) {
        return nullptr;
    }
    easyar_CameraFrameStreamer * cdata;
    easyar_tryCastFrameStreamerToCameraFrameStreamer(v->get_cdata().get(), &cdata);
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<CameraFrameStreamer>(std::shared_ptr<easyar_CameraFrameStreamer>(cdata, [](easyar_CameraFrameStreamer * ptr) { easyar_CameraFrameStreamer__dtor(ptr); }));
}

}

#endif
