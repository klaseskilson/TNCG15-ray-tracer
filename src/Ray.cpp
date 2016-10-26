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

    float r1 = 2*M_PI*uniformRand();
    float r2 = uniformRand();
    float r2squareRoot = sqrt(r2);
    vec3 w = normal;
    vec3 u = normalize((fabs(w.x)>.1?vec3(0, 1, 0):cross(vec3(1.0f),w)));
    vec3 v = cross(w, u);
    vec3 d = normalize((u*(float)cos(r1)*r2squareRoot + v*(float)sin(r1)*r2squareRoot + w*(float)sqrt(1-r2)));
    
    return Ray(position, d);
}
