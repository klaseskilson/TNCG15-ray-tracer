//
// Created by Carl Englund on 2016-10-20.
//

#ifndef TNCG15_SPHERE_H
#define TNCG15_SPHERE_H
#include <glm/glm.hpp>
#include "Ray.h"
#include "Surface.h"

class Sphere {
public:
    Sphere(glm::vec3 v = glm::vec3(), float f = 0.0f, Surface s = Surface());
    int sphereIntersection(Ray&, glm::vec3&);
    vec3 getNormal(vec3 point);
    const Surface &getSurface() const;
private:
    glm::vec3 position;
    float radius;
    Surface surface;

};


#endif //TNCG15_SPHERE_H
