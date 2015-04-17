#pragma once
#include "Matrix4.h"

class ProjectionMatrix :
    public Matrix4
{
public:
    ProjectionMatrix(float FOV, float aspect_ratio, float near, float far);
    ~ProjectionMatrix();

    void ProjectionMatrix::setProjectionMatrix(float FOV, float aspect, float near, float far);
};

