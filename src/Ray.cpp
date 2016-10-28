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
    double rand1 = uniformRand();
    double rand2 = uniformRand();

    glm::vec3 helper = normal + glm::vec3(1,1,1);
    glm::vec3 tangent = glm::normalize(glm::cross(normal, helper));
    float inclination = acos(sqrt(rand1));
    float azimuth = 2 * M_PI * rand2;
    // Change the actual vector
    glm::vec3 random_direction = normal;
    random_direction = glm::normalize(glm::rotate(
            random_direction,
            inclination,
            tangent));
    random_direction = glm::normalize(glm::rotate(
            random_direction,
            azimuth,
            normal));

    return Ray(position, random_direction);
}
