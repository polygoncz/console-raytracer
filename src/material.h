#ifndef MATERIAL_H
#define MATERIAL_H

#include "core.h"

#include "color.h"

/**
 * Rozhraní, které definuje metody, které musejí implementovat konkrétní materiály.
 * Třída Material dědí z třídy ReferenceCounted, takže může být předávána pomocí
 * instance třídy Reference<Material>.
 */
class Material
{
public:
    /**
     * Virtuální destruktor.
     */
    virtual ~Material();

    /**
     * Vypocita a vrati barvu materialu (neni zavisla na materialu).
     * @return barva materialu.
     */
    virtual RGBColor f(const Vector& wi, Vector& wo, const Normal& n) const = 0;
};

class Matte : public Material
{
public:
    Matte(const RGBColor& base, float kd);
    Matte(const Matte& m);
    virtual ~Matte();

    virtual RGBColor f(const Vector& wi, Vector& wo, const Normal& n) const;

private:
    RGBColor base;
    float kd;
};

#endif // MATERIAL_H
