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

Ray Ray::sampleHemisphere(const Ray &outgoing, const vec3 normal) const{
    double phi = randMinMax(0.0, 2.0 * M_PI);
    double theta = randMinMax(0.0, M_PI / 2.0);

    vec3 d(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));

    // ensure proper direction
    d = glm::dot(d, normal) < 0 ? d : -d;
    return Ray(outgoing.start, d);
}
