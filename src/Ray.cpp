#include "Ray.h"

Ray::Ray(glm::vec3 s, glm::vec3 d) {
    start = s;
    direction = d;
}

Ray Ray::bounce(const vec3 &position, const vec3 &normal) const {
    glm::vec3 newDirection = glm::reflect(direction, normal);
    Ray r(position, newDirection);
    return r;
}

void Ray::setColor(const ColorDouble &clr) {
    color = clr;
}
