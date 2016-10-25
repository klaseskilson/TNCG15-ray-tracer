#include "Surface.h"

ColorDouble Surface::reflect(const Ray &in, const Ray &out, const Direction &normal) const {
    switch (reflectionModel) {
        case LAMBERTIAN:
            return lambertianReflection();
        case SPECULAR:
            return lambertianReflection();
        default:
            std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
            return ColorDouble(0.0);
    }
}

ColorDouble Surface::lambertianReflection() const {
    return color * (double)reflectionCoefficient / M_PI;
}

ColorDouble Surface::specularReflection(const Ray &in, const Direction &normal) const {
    vec3 direction = in.getDirection();
    return direction;// - dot(direction, normal)*normal;
}

float Surface::getReflectionCoefficient() const {
    return reflectionCoefficient;
}

Ray Surface::bounceRay(const Ray &in, const vec3 &position, const Direction &normal) const {
    switch (reflectionModel) {
        case LAMBERTIAN:
            return in.sampleHemisphere(position, normal);
        case SPECULAR:
            return in.bounce(position, normal);
        default:
            std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
            Ray r;
            return r;
    }
}
