#include "film.h"

#include "color.h"

Film::Film(size_t w, size_t h, float size)
    : _width(w), _height(h), _size(size)
{
    _pixelCount = w * h;
    data = new RGBColor[_pixelCount];
}

Film::~Film()
{
    delete [] data;
    data = 0;
}

size_t Film::pixelCount() const
{
    return _width * _height;
}

size_t Film::width() const
{
    return _width;
}

size_t Film::height() const
{
    return _height;
}

float Film::size() const
{
    return _size;
}

void Film::setPixelColor(const RGBColor& c, const size_t w, const size_t h)
{
    size_t index = offset(w, h);
    data[index] = c;
}

RGBColor Film::getPixelColor(const size_t w, const size_t h) const
{
    return data[offset(w, h)];
}
