#include "camera.h"

#include "film.h"
#include "geometry.h"

Camera::~Camera()
{}

PerspectiveCamera::~PerspectiveCamera()
{}

Ray PerspectiveCamera::generateRay(const CameraSample& sample) const
{
    Pixel p;

    p.x = film->size() * (sample.x - 0.5f * (film->width() - 1.f));
    p.y = film->size() * (sample.y - 0.5f * (film->height() - 1.f));

    Vector dir = p.x * u + p.y * v - d * w;
    dir.normalize();

    return Ray(eye, dir);
}
