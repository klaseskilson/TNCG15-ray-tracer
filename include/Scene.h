#ifndef TNCG15_SCENE_H
#define TNCG15_SCENE_H

#include <array>
#include <list>
#include <vector>
#include "Triangle.h"
#include "Ray.h"
#include "Sphere.h"

struct TriangleIntersection {
    Triangle triangle;
    glm::vec3 point;
};

struct SphereIntersection {
    Sphere sphere;
    glm::vec3 point;
};

struct ObjectIntersection {
    SceneObject *object;
    vec3 point;
};

class Scene {
public:
    Scene();
    void createRoom();
    std::list<ObjectIntersection> detectIntersections(Ray ray);
    void importTriangles(std::vector<Triangle> triangles);
    void importTriangle(Triangle &t);
    std::list<SphereIntersection> detectSphereIntersections(Ray ray);

private:
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;

};


#endif //TNCG15_SCENE_H
