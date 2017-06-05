//=============================================================================================================================
//
// EasyAR 2.0.0
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TYPES_HPP__
#define __EASYAR_TYPES_HPP__

#include "easyar/types.h"
#include <cstddef>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <stdexcept>

namespace easyar {

static inline std::shared_ptr<easyar_String> std_string_to_easyar_String(std::string s)
{
    easyar_String * ptr;
    easyar_String_from_utf8(s.data(), s.data() + s.size(), &ptr);
    return std::shared_ptr<easyar_String>(ptr, [](easyar_String * ptr) { easyar_String__dtor(ptr); });
}
static inline std::string std_string_from_easyar_String(std::shared_ptr<easyar_String> s)
{
    return std::string(easyar_String_begin(s.get()), easyar_String_end(s.get()));
}

enum class CloudStatus
{
    Success = 0,
    Reconnecting = 1,
    Fail = 2,
};

class CloudRecognizer;

class Drawable;

class Frame;

enum class PixelFormat
{
    Unknown = 0,
    Gray = 1,
    YUV_NV21 = 2,
    YUV_NV12 = 3,
    RGB888 = 4,
    BGR888 = 5,
    RGBA8888 = 6,
};

class Image;

struct Matrix34F;

struct Matrix44F;

struct Vec4F;

struct Vec3F;

struct Vec2F;

struct Vec4I;

struct Vec2I;

enum class CameraDeviceFocusMode
{
    Normal = 0,
    Triggerauto = 1,
    Continousauto = 2,
    Infinity = 3,
    Macro = 4,
};

enum class CameraDeviceType
{
    Default = 0,
    Back = 1,
    Front = 2,
};

class CameraCalibration;

class CameraDevice;

enum class PermissionStatus
{
    Granted = 0x00000000,
    Denied = 0x00000001,
    Error = 0x00000002,
};

enum class VideoStatus
{
    Error = -1,
    Ready = 0,
    Completed = 1,
};

enum class VideoType
{
    Normal = 0,
    TransparentSideBySide = 1,
    TransparentTopAndBottom = 2,
};

class VideoPlayer;

enum class RendererAPI
{
    Auto = 0,
    None = 1,
    GLES2 = 2,
    GLES3 = 3,
    GL = 4,
    D3D9 = 5,
    D3D11 = 6,
    D3D12 = 7,
};

class Renderer;

class Engine;

class FrameFilter;

class FrameStreamer;

class CameraFrameStreamer;

class QRCodeScanner;

enum class StorageType
{
    App = 0,
    Assets = 1,
    Absolute = 2,
    Json = 0x00000100,
};

class Target;

enum class TargetStatus
{
    Unknown = 0,
    Undefined = 1,
    Detected = 2,
    Tracked = 3,
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
