#pragma once

#include "Vector4.h"
#include "Color.h"
#include "Object.h"

class Light : public Object
{
protected:
    Color color;
public:
    Light();
    Light(double x, double y, double z, float r, float g, float b);
    ~Light();

    Color& getColor();
};

