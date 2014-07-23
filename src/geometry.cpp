#include "geometry.h"

Vector::Vector(const Point& n)
    : x(n.x), y(n.y), z(n.z)
{
}

Vector::Vector(const Normal& n)
    : x(n.x), y(n.y), z(n.z)
{
}
