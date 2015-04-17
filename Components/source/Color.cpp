#include "Color.h"

Color::Color()
{
    r = g = b = 0.0;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::operator*(const Color& c) const
{
    return Color(r * c.r, g * c.r, b * c.b);
}

Color Color::operator*(double a) const
{
    return Color(r * a, g * a, b * a);
}

Color& Color::operator+=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return (*this);
}