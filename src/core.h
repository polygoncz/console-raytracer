#pragma once

#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include <cmath>

#define EPSILON 0.0001f

#ifndef M_PI
#define M_PI 3.1415926f
#endif

class  Point;
class  Vector;
class  Normal;
class  Vector;
class  Ray;
struct Intersection;
class  Film;
class  RGBColor;
class  Light;
class  Primitive;
class  Camera;
class  Material;

template<class T>
inline T clamp(const T& val, T& from, T& to)
{
    if (from > to)
        std::swap(from, to);

    const T t = val < from ? to : val;
    return t > to ? from : t;
}


inline bool solveQuadratic(float a, float b, float c, float *t0, float *t1)
{
    float discrim = b * b - 4.f * a * c;
    if (discrim < 0.f) return false;
    float rootDiscrim = std::sqrt(discrim);

    float q;
    if (b < 0.f)
        q = -.5f * (b - rootDiscrim);
    else
        q = -.5f * (b + rootDiscrim);
    *t0 = q / a;
    *t1 = c / q;
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}

#endif // CORE_H
