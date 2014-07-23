#include "primitive.h"

#include <algorithm>

#include "geometry.h"
#include "intersection.h"

std::shared_ptr<Material> Primitive::getMaterial(void)
{
    return material;
}

void Primitive::setMaterial(const std::shared_ptr<Material>& material)
{
    this->material = material;
}

Primitive::~Primitive()
{}


//Sphere
Sphere::Sphere(const Point& center, float radius,
               const std::shared_ptr<Material> material)
    : Primitive(material), center(center), radius(radius)
{}

Sphere::Sphere(const Sphere& sphere)
    : Primitive(sphere.material), center(sphere.center), radius(sphere.radius)
{}

Sphere::~Sphere()
{}

bool Sphere::intersectP(const Ray& ray)
{
    Vector temp = ray.o - center;
    float a = dot(ray.d, ray.d);
    float b = 2 * dot(temp, ray.d);
    float c = dot(temp, temp) - radius * radius;

    float t1, t2;

    if (solveQuadratic(a, b, c, &t1, &t2)) {
        float t = std::min(t1, t2);
        if (t > EPSILON) {
            return true;
        }
    }

    return false;
}

bool Sphere::intersect(const Ray& ray, Intersection& inter)
{
    Vector temp = ray.o - center;
    float a = dot(ray.d, ray.d);
    float b = 2 * dot(temp, ray.d);
    float c = dot(temp, temp) - radius * radius;

    float t1, t2;

    if (solveQuadratic(a, b, c, &t1, &t2)) {
        float t = std::min(t1, t2);

        if (t > EPSILON && t < inter.t) {
            ray.rayEpsilon = 1e-3f * t;
            inter.normal = (temp + ray.d * t) / radius;
            inter.ray = ray;
            inter.t = t;
            inter.hitPoint = ray(t);
            inter.hitObject = true;
            inter.material = getMaterial();

            return true;
        }
    }

    return false;
}
