#pragma once

#include "Color.h"
#include "Camera.h"
#include "Light.h"

extern void API_Normal(double x, double y, double z);
extern void API_drawPoint(double x, double y, double z);
extern void API_setCamera(const Camera &camera);
extern void API_setProjectionMatrix(double p_FOV, double p_near, double p_far);
extern void API_setProjectionMatrix(double p_FOV);
extern void API_setColor(const Color& c);
extern void API_loadIdentity();
extern void API_multMatrix(const Matrix4& m);
extern void API_addLightSource(const Light& light);

enum tShadeType
{
    none = 0x00,
    diffuse = 0x01,
    speculer = 0x02,
    ambient = 0x04
};
typedef UINT8 ShadeType;