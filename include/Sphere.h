//
// Created by Carl Englund on 2016-10-20.
//

#ifndef TNCG15_SPHERE_H
#define TNCG15_SPHERE_H
#include <glm/glm.hpp>
#include "Ray.h"


class Sphere {
public:
    Sphere(glm::vec3 v = glm::vec3(), float f = 0.0f, ColorDouble c = ColorDouble());
    int sphereIntersection(Ray&, glm::vec3&);
    const ColorDouble &getColor() const;

private:
    glm::vec3 position;
    float radius;
    ColorDouble color;

};


#endif //TNCG15_SPHERE_H
