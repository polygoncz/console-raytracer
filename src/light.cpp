#include "light.h"

Light::~Light()
{}

PointLight::PointLight(const RGBColor& c, float ls, const Point& loc)
    : c(c), ls(ls), loc(loc)
{}

PointLight::PointLight(const PointLight& p)
    : c(p.c), ls(p.ls), loc(p.loc)
{}

PointLight::~PointLight()
{}

Vector PointLight::getDirection(const Intersection& inter) const
{
    Vector dir = loc - inter.hitPoint;
    return dir.normalize();
}

RGBColor PointLight::l(const Intersection& inter) const
{
    return ls * c;
}
