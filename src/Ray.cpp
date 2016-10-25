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

Ray Ray::sampleHemisphere(const vec3 position, const vec3 normal) const{

    float r1 = uniformRand();
    float r2 = uniformRand();
    float theta = r1 * M_1_PI * 2.0f;
    float phi = acos(r2);
    vec3 v1 = glm::vec3(cos(theta)*sin(phi), sin(phi)*sin(theta), cos(phi));
    
    return Ray(position, v1);
}
