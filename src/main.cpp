#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

//Main includes
#include "core.h"

#include "camera.h"
#include "color.h"
#include "film.h"
#include "geometry.h"
#include "intersection.h"
#include "light.h"
#include "material.h"
#include "primitive.h"

//deklarace globalnich promennych
using namespace std;

typedef shared_ptr<Light> LightPtr;
typedef shared_ptr<Primitive> PrimitivePtr;
typedef shared_ptr<Film> FilmPtr;
typedef shared_ptr<Camera> CameraPtr;

vector<LightPtr> lights;
vector<PrimitivePtr> objects;

RGBColor backgroud;

FilmPtr film;
CameraPtr camera;

bool intersect(const Ray& ray, Intersection& inter)
{
    for (auto object : objects) {
        object->intersect(ray, inter);
    }

    return inter.hitObject;
}

bool intersectP(const Ray& ray)
{
    for (auto object : objects) {
        if (object->intersectP(ray))
            return true;
    }

    return false;
}

void renderLoop()
{
    size_t pixelCompleted = 0;

    for (size_t r = 0; r < film->height(); ++r) {
        for (size_t c = 0; c < film->width(); ++c) {
            Ray ray = camera->generateRay( { (float) r, (float) c } );
            Intersection inter;

            intersect(ray, inter);

            if (inter.hitObject) { //pokud protne objekt
                RGBColor color;
                for (auto light : lights) {
                    const Vector shDir = light->getDirection(inter);
                    Ray shadowRay(inter.hitPoint, shDir);

                    if (!intersectP(shadowRay)) {
                        float ndotwi = dot(inter.normal, shDir);
                        if (ndotwi > 0.f)
                            color += inter.material->f(shDir, ray.d, inter.normal) * light->l(inter) * ndotwi;
                    }
                }

                film->setPixelColor(color, c, r);
            } else { //pokud neprotne tak vypln barvou pozadi
                film->setPixelColor(backgroud, c, r);
            }
        }
    }
}

void saveImageToPPM(const shared_ptr<Film>& film, const string& path)
{
    std::ofstream ofs(path, ios::binary | ios::out);

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

    //LightPtr pl1(new PointLight(WHITE, 0.5f, Point(10.f, 10.f, 10.f)));
    LightPtr pl2(new PointLight(RED, 2.f, Point(10.f, 10.f, -10.f)));
    //LightPtr pl3(new PointLight(WHITE, 1.f, Point(-10.f, 10.f, 5.f)));

//    lights.push_back(pl1);
    lights.push_back(pl2);
//    lights.push_back(pl3);
}

int main(int argc, char* argv[])
{
    string path;

    if (argc == 2)
        path = argv[1];
    else
        path = "output.ppm";

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

    saveImageToPPM(film, path);

    cout << "Save into: " << path << endl;

    return 0;
}
