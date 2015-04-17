#include "ViewPortMatrix.h"

ViewPortMatrix::ViewPortMatrix(float window_width, float window_height)
{
    setViewPortMatrix(window_width, window_height);
}

ViewPortMatrix::~ViewPortMatrix()
{
}

void ViewPortMatrix::setViewPortMatrix(float window_width, float window_height)
{
    this->identity();
    m[0][0] = window_width / 2.0;
    m[0][3] = window_width / 2.0;
    m[1][1] = window_height / 2.0;
    m[1][3] = window_height / 2.0;
    m[2][2] = 1.0 / 2.0;
    m[2][3] = 1.0 / 2.0;        
}
