//=============================================================================================================================
//
// EasyAR 2.0.0
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGE_HPP__
#define __EASYAR_IMAGE_HPP__

#include "easyar/types.hpp"

namespace easyar {

class Image
{
protected:
    std::shared_ptr<easyar_Image> cdata_;
    void init_cdata(std::shared_ptr<easyar_Image> cdata);
    Image & operator=(const Image & data) = delete;
public:
    Image(std::shared_ptr<easyar_Image> cdata);
    virtual ~Image();

    std::shared_ptr<easyar_Image> get_cdata();

    Image();
    std::string typeName();
    int width();
    int height();
    int stride();
    PixelFormat format();
    void * data();
};

}


#endif

#ifndef __IMPLEMENTATION_EASYAR_IMAGE_HPP__
#define __IMPLEMENTATION_EASYAR_IMAGE_HPP__

#include "easyar/image.h"

namespace easyar {

inline Image::Image(std::shared_ptr<easyar_Image> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
inline Image::~Image()
{
    cdata_ = nullptr;
}

inline std::shared_ptr<easyar_Image> Image::get_cdata()
{
    return cdata_;
}
inline void Image::init_cdata(std::shared_ptr<easyar_Image> cdata)
{
    cdata_ = cdata;
}
inline Image::Image()
    :
    cdata_(nullptr)
{
    easyar_Image * _return_value_;
    easyar_clearException();
    easyar_Image__ctor(&_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    init_cdata(std::shared_ptr<easyar_Image>(_return_value_, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); }));
}
inline std::string Image::typeName()
{
    easyar_String * _return_value_;
    easyar_clearException();
    easyar_Image_typeName(cdata_.get(), &_return_value_);
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
inline int Image::width()
{
    easyar_clearException();
    auto _return_value_ = easyar_Image_width(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline int Image::height()
{
    easyar_clearException();
    auto _return_value_ = easyar_Image_height(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline int Image::stride()
{
    easyar_clearException();
    auto _return_value_ = easyar_Image_stride(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}
inline PixelFormat Image::format()
{
    easyar_clearException();
    auto _return_value_ = easyar_Image_format(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return static_cast<PixelFormat>(_return_value_);
}
inline void * Image::data()
{
    easyar_clearException();
    auto _return_value_ = easyar_Image_data(cdata_.get());
    auto exception = easyar_tryGetException();
    if (exception != nullptr) {
        throw std::runtime_error(exception);
    }
    return _return_value_;
}

}

#endif
