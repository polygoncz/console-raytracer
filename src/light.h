#ifndef LIGHT_H
#define LIGHT_H

#include "core.h"

#include "geometry.h"
#include "color.h"
#include "intersection.h"

/**
 * Rozhraní pro objekty světel. Je možné z nich získat intezitu osvětlení daného bodu
 * a směr k danému bodu.
 */
class Light
{
public:
    /**
     * Virtuální destruktor
     */
    virtual ~Light();

    /**
     * Vypočítá směr světla vzhledme k místu průsečíku.
     * @param sr informace o průsečíku
     * @return Vector směru světla
     */
    virtual Vector getDirection(const Intersection& inter) const = 0;

    /**
     * Provede výpočet světelného příspěvku světla pro průsečík.
     * @param sr informace o průsečíku
     * @return hodnota světelného příspěvku
     */
    virtual RGBColor l(const Intersection& inter) const = 0;
};

class PointLight : public Light
{
public:
    PointLight(const RGBColor& c, float ls, const Point& loc);
    PointLight(const PointLight& p);
    virtual ~PointLight();

    virtual Vector getDirection(const Intersection& inter) const;

    virtual RGBColor l(const Intersection& inter) const;

private:
    RGBColor c;
    float ls;
    Point loc;
};

#endif // LIGHT_H
