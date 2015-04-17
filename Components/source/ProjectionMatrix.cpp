#include "ProjectionMatrix.h"
#include "Utility.h"

ProjectionMatrix::ProjectionMatrix(float FOV, float aspect, float near, float far)
{
    setProjectionMatrix(FOV, aspect, near, far);
}

ProjectionMatrix::~ProjectionMatrix()
{
}

void ProjectionMatrix::setProjectionMatrix(float FOV, float aspect, float near, float far)
{
    this->identity();
    FOV = degree2rad(FOV);
    m[0][0] = 1.0 / (aspect * tan(FOV / 2.0));
    m[1][1] = 1.0 / (tan(FOV / 2.0));
    m[2][2] = (near + far) / (near - far);
    m[2][3] = (2 * near * far) / (near - far);
    m[3][2] = -1;
    m[3][3] = 0;
}
