#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <memory>
#include <limits>

#include "core.h"

#include "geometry.h"

/**
 * Struktura uchovává atributy, které představují souhrn
 * informací o průsečíku paprsku s objektem ve scéně.
 * Všechny její atributy jsou veřejné.
 */
struct Intersection {
    Intersection()
        : hitObject(false), material(0), depth(0), t(std::numeric_limits<float>::max())
    {
    }

    Intersection(const Intersection& sr)
        : hitObject(sr.hitObject), hitPoint(sr.hitPoint), normal(sr.normal),
          ray(sr.ray), material(sr.material), depth(sr.depth), t(sr.t)
    {
    }

    bool hitObject; ///< protnul paprsek objekt?
    Point hitPoint; ///< Souřadnice místa dopadu
    Normal normal; ///< Normála v místě dopadu
    Ray ray; ///< Paprsek, pro který se provádí výpočet
    std::shared_ptr<Material> material; ///< Reference na materiál objektu
    int depth; ///< Hloubka rekurze
    float t; ///< hodnota parametru t v místě dopadu
};

#endif // INTERSECTION_H
