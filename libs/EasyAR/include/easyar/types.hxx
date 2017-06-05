//=============================================================================================================================
//
// EasyAR 2.0.0
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TYPES_HXX__
#define __EASYAR_TYPES_HXX__

#include "easyar/types.h"
#include <cstddef>

namespace easyar {

class String
{
private:
    easyar_String * cdata_;
    virtual String & operator=(const String & data) { return *this; } //deleted
public:
    String(easyar_String * cdata)
        : cdata_(cdata)
    {
    }
    virtual ~String()
    {
        if (cdata_) {
            easyar_String__dtor(cdata_);
            cdata_ = NULL;
        }
    }

    String(const String & data)
        : cdata_(static_cast<easyar_String *>(NULL))
    {
        easyar_String_copy(data.cdata_, &cdata_);
    }
    const easyar_String * get_cdata() const
    {
        return cdata_;
    }
    easyar_String * get_cdata()
    {
        return cdata_;
    }

    static void from_utf8(const char * begin, const char * end, /* OUT */ String * * Return)
    {
        easyar_String * _return_value_ = NULL;
        easyar_String_from_utf8(begin, end, &_return_value_);
        *Return = _return_value_ == NULL ? NULL : new String(_return_value_);
    }
    static void from_utf8_begin(const char * begin, /* OUT */ String * * Return)
    {
        easyar_String * _return_value_ = NULL;
        easyar_String_from_utf8_begin(begin, &_return_value_);
        *Return = _return_value_ == NULL ? NULL : new String(_return_value_);
    }
    const char * begin()
    {
        return easyar_String_begin(cdata_);
    }
    const char * end()
    {
        return easyar_String_end(cdata_);
    }
};

inline void clearException()
{
    easyar_clearException();
}

inline const char * tryGetException()
{
    return easyar_tryGetException();
}

enum CloudStatus
{
    CloudStatus_Success = 0,
    CloudStatus_Reconnecting = 1,
    CloudStatus_Fail = 2,
};

class CloudRecognizer;

class Drawable;

class Frame;

enum PixelFormat
{
    PixelFormat_Unknown = 0,
    PixelFormat_Gray = 1,
    PixelFormat_YUV_NV21 = 2,
    PixelFormat_YUV_NV12 = 3,
    PixelFormat_RGB888 = 4,
    PixelFormat_BGR888 = 5,
    PixelFormat_RGBA8888 = 6,
};

class Image;

struct Matrix34F;

struct Matrix44F;

struct Vec4F;

struct Vec3F;

struct Vec2F;

struct Vec4I;

struct Vec2I;

enum CameraDeviceFocusMode
{
    CameraDeviceFocusMode_Normal = 0,
    CameraDeviceFocusMode_Triggerauto = 1,
    CameraDeviceFocusMode_Continousauto = 2,
    CameraDeviceFocusMode_Infinity = 3,
    CameraDeviceFocusMode_Macro = 4,
};

enum CameraDeviceType
{
    CameraDeviceType_Default = 0,
    CameraDeviceType_Back = 1,
    CameraDeviceType_Front = 2,
};

class CameraCalibration;

class CameraDevice;

enum PermissionStatus
{
    PermissionStatus_Granted = 0x00000000,
    PermissionStatus_Denied = 0x00000001,
    PermissionStatus_Error = 0x00000002,
};

enum VideoStatus
{
    VideoStatus_Error = -1,
    VideoStatus_Ready = 0,
    VideoStatus_Completed = 1,
};

enum VideoType
{
    VideoType_Normal = 0,
    VideoType_TransparentSideBySide = 1,
    VideoType_TransparentTopAndBottom = 2,
};

class VideoPlayer;

enum RendererAPI
{
    RendererAPI_Auto = 0,
    RendererAPI_None = 1,
    RendererAPI_GLES2 = 2,
    RendererAPI_GLES3 = 3,
    RendererAPI_GL = 4,
    RendererAPI_D3D9 = 5,
    RendererAPI_D3D11 = 6,
    RendererAPI_D3D12 = 7,
};

class Renderer;

class Engine;

class FrameFilter;

class FrameStreamer;

class CameraFrameStreamer;

class QRCodeScanner;

enum StorageType
{
    StorageType_App = 0,
    StorageType_Assets = 1,
    StorageType_Absolute = 2,
    StorageType_Json = 0x00000100,
};

class Target;

enum TargetStatus
{
    TargetStatus_Unknown = 0,
    TargetStatus_Undefined = 1,
    TargetStatus_Detected = 2,
    TargetStatus_Tracked = 3,
};

class TargetInstance;

class TargetTracker;

class ImageTarget;

class ImageTracker;

struct FunctorOfVoidFromCloudStatus;

struct FunctorOfVoidFromCloudStatusAndListOfPointerOfTarget;

class ListOfPointerOfTarget;

class ListOfPointerOfImage;

class ListOfPointerOfTargetInstance;

struct FunctorOfVoidFromPermissionStatusAndString;

struct FunctorOfVoidFromVideoStatus;

struct FunctorOfVoidFromPointerOfTargetAndBool;

class ListOfPointerOfImageTarget;


}

#endif
