#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>


//Main includes
//#include "core.h"

#include "camera.h"
#include "color.h"
#include "film.h"
#include "geometry.h"
#include "intersection.h"
#include "light.h"
#include "material.h"
#include "primitive.h"

using namespace std;

//typedefy pro kratsi psani
typedef shared_ptr<Light> LightPtr;
typedef shared_ptr<Primitive> PrimitivePtr;
typedef shared_ptr<Film> FilmPtr;
typedef shared_ptr<Camera> CameraPtr;

//deklarace globalnich promennych
vector<LightPtr> lights; ///< buffer svetel
vector<PrimitivePtr> objects; ///< buffer objektu

RGBColor backgroud; ///< pozadi obrazku

FilmPtr film; ///< film v kamere - vhodne mit ho zde pro pristup k datum obrazku
CameraPtr camera; ///< kamera ve scene

string filename = "output.ppm"; ///< cesta k souboru, nastavena vychozi hodnota

/*!
 * \brief Najde nejblizsi prusecik paprsku s objekty ve scene.
 * \param [in]  ray paprsek
 * \param [out] inter objekt do ktereho se ukladaji data o pruseciku
 * \return
 */
bool intersect(const Ray& ray, Intersection& inter)
{
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        auto object = *it;
        object->intersect(ray, inter);
    }

    return inter.hitObject;
}

/*!
 * \brief Zjednodusena verze funkce intersect(const Ray&, Intersection&) pro vypocet stinu.
 * \param ray paprsek
 * \return
 */
bool intersectP(const Ray& ray)
{
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        auto object = *it;
        if (object->intersectP(ray))
            return true;
    }

    return false;
}

/*!
 * \brief Metoda hlavni renderovaci smycky.
 */
void renderLoop()
{
    //pro vsechny pixely
    for (size_t r = 0; r < film->height(); ++r) {
        for (size_t c = 0; c < film->width(); ++c) {
            //provede transformaci paprsku
            CameraSample s;
            s.x = static_cast<float>(r);
            s.y = static_cast<float>(c);

            Ray ray = camera->generateRay(s);

            Intersection inter;
            intersect(ray, inter);

            //pokud protne objekt
            if (inter.hitObject) {
                //svetelne prispevky od jednotlivych svetel
                RGBColor color;
                for (auto it = lights.begin(); it != lights.end(); ++it) {
                    auto light = *it;
                    const Vector shDir = light->getDirection(inter);
                    Ray shadowRay(inter.hitPoint, shDir);

                    //implementace stinu
                    if (!intersectP(shadowRay)) {
                        //vypocet svetelneho prispevku pro jednotliva svetla
                        float ndotwi = dot(inter.normal, shDir); // "zeslabovaci faktor"
                        if (ndotwi > 0.f)
                            color += inter.material->f(shDir, ray.d, inter.normal)
                                     * light->l(inter) * ndotwi;
                    }
                }

                film->setPixelColor(color, c, r);
            } else { //pokud neprotne tak vypln barvou pozadi
                film->setPixelColor(backgroud, c, r);
            }
        }
    }
}

/*!
 * \brief Ukladani dat z filmu do obrazku typu PPM.
 * \param film objekt filmu, ktery chceme ulozit
 * \param path cesta (absolutni, relativni)
 */
void saveImageToPPM(const shared_ptr<Film>& film, const string& path)
{
    ofstream ofs(path, ios::binary | ios::out);

    ofs << "P6\n" << film->width() << " " << film->height() << "\n255\n";

    for (size_t j = 0; j < film->height(); ++j) {
        for (size_t i = 0; i < film->width(); ++i) {
            RGBColor c = film->getPixelColor(j, i).clamp();
            unsigned char r = (unsigned char)(c.r * 255.f);
            unsigned char g = (unsigned char)(c.g * 255.f);
            unsigned char b = (unsigned char)(c.b * 255.f);
            ofs << r << g << b;
        }
    }

    ofs.close();
}

/*!
 * \brief Tato metoda slouzi k inicializaci globalnich promennych, ktere predstavuji scenu.
 */
void build()
{
    backgroud = GREY;

    film = make_shared<Film>(800, 800, 0.05f);
    camera = make_shared<PerspectiveCamera>(
                 Point(5.f, 5.f, 5.f),
                 Point(),
                 Vector(0.f, 1.f, 0.f),
                 film,
                 50.f
             );

    PrimitivePtr sphere(new Sphere(
                            Point(0.f, 0.f, 0.f),
                            2.f,
                            make_shared<Matte>(RED, 0.8f)
                        ));
    objects.push_back(sphere);

    LightPtr pl2(new PointLight(RED, 2.f, Point(10.f, 10.f, -10.f)));

    lights.push_back(pl2);
}

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char* argv[])
{
    if (argc == 2)
        filename = argv[1];

    clock_t start, end;

    start = clock();
    build();
    end = clock();
    double buildTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << endl;
    cout << "Build time: " << buildTime << endl;

    start = clock();
    renderLoop();
    end = clock();
    double renderTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Render time: " << renderTime << endl;

    saveImageToPPM(film, filename);

    cout << "Save into: " << filename << endl;

    return 0;
}
