//=============================================================================================================================
//
// Copyright (c) 2015-2017 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#pragma once

#include <easyar/vector.hpp>
#include <easyar/matrix.hpp>

class BoxRenderer
{
public:
    void init();
    void render(const easyar::Matrix44F& projectionMatrix, const easyar::Matrix44F& cameraview, easyar::Vec2F size);
private:
    unsigned int program_box;
    int pos_coord_box;
    int pos_color_box;
    int pos_trans_box;
    int pos_proj_box;
    unsigned int vbo_coord_box;
    unsigned int vbo_color_box;
    unsigned int vbo_color_box_2;
    unsigned int vbo_faces_box;
};
