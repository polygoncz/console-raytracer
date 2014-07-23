#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "core.h"

#include "geometry.h"

/**
 * Struktura která, určuje polohu vzorku na filmu kamery.
 * Počítáno dle zvyklostí od levého horního rohu.
 */
struct CameraSample {
    float x, y;
};

typedef CameraSample Pixel; ///< sémantika

/**
 * Bázová třída kamery. Hlavní schopností je generování paprsku
 * na základě polohy vzorku na filmu.
 */
class Camera
{
public:
    /**
     * Konstruktor.
     * @param eye bod pozorovatele
     * @param target cíl pozorování
     * @param up vektor natočení
     * @param exposure expozice (FUTURE)
     */
    Camera(const Point& eye, const Point& target, const Vector& up, std::shared_ptr<Film> film)
        : eye(eye), target(target), up(up), film(film)
    {
        computeUVW();
    }

    /**
     * Virtuální destruktor.
     */
    virtual ~Camera();

    /**
     * Na základě zadaných parametrů v podobě vzorku na filmu kamery vypočítá
     * odpovídající transformovaný paprsek. Implementace je potom provedena
     * v potomcích třídy.
     * @param sample vzorek na filmu kamery
     * @param ray ukazatel na instanci třídy Ray, slouží jako návratová hodnota
     */
    virtual Ray generateRay(const CameraSample& sample) const = 0;

protected:
    /**
     * Výpočet ortonormální báze pohledu.
     */
    void computeUVW()
    {
        w = eye - target;
        w.normalize();
        u = cross(up, w);
        u.normalize();
        v = cross(u, w);
        v.normalize();
    }

protected:
    Point eye; ///< Bod pozorovatele.
    Point target; ///< Bod cíle pozorování.
    Vector up; ///< Vektor natočení kamery.
    std::shared_ptr<Film> film; ///< Ukazatel na film.
    Vector u; ///< Vektor ortonormální báze pohledu
    Vector v; ///< Vektor ortonormální báze pohledu
    Vector w; ///< Vektor ortonormální báze pohledu
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(const Point& eye, const Point& target, const Vector& up,
                      std::shared_ptr<Film> film, float d)
        : Camera(eye, target, up, film), d(d)
    {}

    virtual ~PerspectiveCamera();

    virtual Ray generateRay(const CameraSample& sample) const;

private:
    float d;
};

#endif // CAMERA_H
