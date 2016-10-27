#include "Surface.h"

ColorDouble Surface::reflect(const Ray &in, const Ray &out, const Direction &normal) const {
    switch (reflectionModel) {
        case LAMBERTIAN:
            return lambertianReflection();
        case SPECULAR:
            return specularReflection();
        default:
            std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
            return ColorDouble(0.0);
    }
}

ColorDouble Surface::lambertianReflection() const {
    return color * (double)reflectionCoefficient / M_PI;
}

ColorDouble Surface::specularReflection() const {
    return color;
}

float Surface::getReflectionCoefficient() const {
    return reflectionCoefficient;
}

Ray Surface::bounceRay(const Ray &in, const vec3 &position, const Direction &normal) const {
    switch (reflectionModel) {
        case LAMBERTIAN:
            return in.sampleHemisphere(in.bounce(position, normal), normal);
        case SPECULAR:
            return in.bounce(position, normal);
        default:
            std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
            Ray r;
            return r;
    }
}

const ColorDouble &Surface::getColor() const {
    return color;
}

int Surface::getReflectionModel() const {
    return reflectionModel;
}
