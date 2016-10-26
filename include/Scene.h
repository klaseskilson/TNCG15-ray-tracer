#ifndef TNCG15_SCENE_H
#define TNCG15_SCENE_H

#include <array>
#include <list>
#include <vector>
#include "Triangle.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"

struct TriangleIntersection {
    Triangle triangle;
    glm::vec3 point;
};

struct SphereIntersection {
    Sphere sphere;
    glm::vec3 point;
};

class Scene {
public:
    Scene();
    void createRoom();
    std::list<TriangleIntersection> detectIntersections(Ray ray);
    void importTriangles(std::vector<Triangle> triangles);
    void importTriangle(Triangle &t);
    std::list<SphereIntersection> detectSphereIntersections(Ray ray);
    void addLight(const Light &l) {
        lights.push_back(l);
    }

private:
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
    std::list<Light> lights;

};


#endif //TNCG15_SCENE_H
