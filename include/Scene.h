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

class Scene {
public:
    Scene();
    void createRoom();
    void createBox(glm::vec3 position, float length);
    std::list<TriangleIntersection> detectIntersections(Ray ray);
    std::list<Sphere> detectSphereIntersections(Ray ray);

private:
    std::vector<Triangle> triangles;
    std::vector<Sphere> spheres;

};


#endif //TNCG15_SCENE_H
