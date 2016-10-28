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

Ray Ray::sampleHemisphere(const vec3 &position, const vec3 normal) const{
    float r1 = 2.0 * M_PI * uniformRand();
    float r2 = uniformRand();
    float r2squareRoot = sqrt(r2);
    vec3 u = glm::normalize((fabs(normal.x) > 0.1 ? vec3(0.0, 1.0, 0.0) : glm::cross(vec3(1.0), normal)));
    vec3 v = glm::cross(normal, u);
    vec3 d = glm::normalize((u * (float)cos(r1) * r2squareRoot + v * (float)sin(r1) * r2squareRoot + normal * (float)sqrt(1-r2)));

    // ensure proper direction
    if (glm::dot(d, normal) < 0) {
        d = -d;
    }

    return Ray(position, d);
}

void Ray::setDirection(const vec3 &direction) {
    Ray::direction = direction;
}
