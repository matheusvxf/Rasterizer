#pragma once
#include "Matrix4.h"

class ViewPortMatrix :
    public Matrix4
{
public:
    ViewPortMatrix(float window_width, float window_height);
    ~ViewPortMatrix();

    void setViewPortMatrix(float window_width, float window_height);
};

