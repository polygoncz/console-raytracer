#include "material.h"

Material::~Material()
{}

Matte::Matte(const RGBColor& base, float kd)
    : base(base), kd(kd)
{}

Matte::Matte(const Matte& m)
    : base(m.base), kd(m.kd)
{}

Matte::~Matte()
{}

RGBColor Matte::f(const Vector& wi, Vector& wo, const Normal& n) const
{
    RGBColor ret = (kd * base) / M_PI;
    return ret;
}
