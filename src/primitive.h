#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>

#include "core.h"

#include "geometry.h"

/**
 * Bázová třída pro objekty, které představují geomettrická tělesa.
 * Implementuje metody pro práci s materiály.
 */
class Primitive
{
public:
    /**
     * Kontruktor s parametrem materiálu.
     * @param _mat materiál nového tělesa
     */
    Primitive(const std::shared_ptr<Material>& mat)
        : material(mat)
    {}

    /**
     * Kopírovací konstruktor
     * @param prm kopírovaná instance
     */
    Primitive(const Primitive& p)
        : material(p.material)
    {}

    /**
     * Virtuální konstruktor.
     */
    virtual ~Primitive();

    /**
     * Výchozí implementace metody @a Primitive::Intersect(const Ray&, Intersection&).
     * @see Primitive::Intersect(const Ray&, Intersection&)
     * @return false
     */
    virtual bool intersect(const Ray& ray, Intersection& inter) = 0;

    /**
     * Výchozí implementace metody @a Primitive::IntersectP(const Ray&)
     * @see Primitive::IntersectP(const Ray&)
     * @return false
     */
    virtual bool intersectP(const Ray& ray) = 0;

    /**
     * Získá materiál tělesa.
     * @return Reference na Material tělesa
     */
    std::shared_ptr<Material> getMaterial(void);

    /**
     * Nastaví materiál tělesa.
     * @param _material nově nastavený materiál
     */
    void setMaterial(const std::shared_ptr<Material>& material);

protected:
    std::shared_ptr<Material> material; ///< Materiál tělesa.
};

class Sphere : public Primitive
{
public:
    Sphere(const Point& center, float radius,
           const std::shared_ptr<Material> material);
    Sphere(const Sphere& sphere);
    virtual ~Sphere();

    virtual bool intersect(const Ray& ray, Intersection& inter);
    virtual bool intersectP(const Ray& ray);

private:
    Point center;
    float radius;
};

#endif // PRIMITIVE_H
