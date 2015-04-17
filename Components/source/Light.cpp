#include "Light.h"

Light::Light() {}

Light::Light(double x, double y, double z, float r, float g, float b) :
    color(r, g, b)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = 1;
}

Light::~Light()
{
}

Color& Light::getColor()
{
    return color;
}
