#ifndef TNCG15_SCENE_H
#define TNCG15_SCENE_H

#include <array>
#include <list>
#include <vector>
#include <glm/gtx/vector_angle.hpp>
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

const int SHADOW_RAY_COUNT = 2;

static const float INTERSECTION_MARGIN = 0.001f;

class Scene {
public:
    Scene();
    void createRoom();
    std::list<TriangleIntersection> detectIntersections(Ray ray) const;
    std::list<SphereIntersection> detectSphereIntersections(Ray ray) const;
    void importTriangles(std::vector<Triangle> triangles);
    void importTriangle(Triangle &t);
    void addLight(const Light &l) {
        lights.push_back(l);
    }
    void addSphere(const Sphere &s) {
        spheres.push_back(s);
    }
    ColorDouble getLightContribution(const vec3 &point, const vec3 &normal) const;

private:
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;
    std::list<Light> lights;

};


#endif //TNCG15_SCENE_H
