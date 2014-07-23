#pragma once

#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include <cmath>

#define EPSILON 0.0001f

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

inline bool solveQuadratic(const float a, const float b, const float c,
                           float* t1, float* t2)
{
    float d = b*b - 4*a*c;

    if (d < 0) return false;

    if (d == 0) {
        if (t1 && t2)
            *t1 = *t2 = (-b) / (2*a);

        return true;
    }

    if (d > 0) {
        if (t1)
            *t1 = (-b - std::sqrt(d)) / (2*a);
        if (t2)
            *t2 = (-b + std::sqrt(d)) / (2*a);

        return true;
    }

    return false;
}

#endif // CORE_H
