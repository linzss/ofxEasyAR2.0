//=============================================================================================================================
//
// EasyAR 2.0.0
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGE_H__
#define __EASYAR_IMAGE_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_Image__ctor(/* OUT */ easyar_Image * * Return);
void easyar_Image_typeName(const easyar_Image * This, /* OUT */ easyar_String * * Return);
int easyar_Image_width(const easyar_Image * This);
int easyar_Image_height(const easyar_Image * This);
int easyar_Image_stride(const easyar_Image * This);
easyar_PixelFormat easyar_Image_format(const easyar_Image * This);
void * easyar_Image_data(const easyar_Image * This);
void easyar_Image__dtor(easyar_Image * This);
void easyar_Image__retain(const easyar_Image * This, /* OUT */ easyar_Image * * Return);

#ifdef __cplusplus
}
#endif

#endif
