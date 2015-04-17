#pragma once

class Color
{
public:
    float r, g, b;

    Color();
    Color(float r, float g, float b);

    Color operator*(const Color& c) const;
    Color operator*(double a) const;
    Color& Color::operator+=(const Color& c);
};