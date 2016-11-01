#include "Surface.h"

Surface::Surface(const ColorDouble &color, const int &model) : color(color), reflectionModel(model) {
    if (model == LIGHTSOURCE) {
        emission = ColorDouble(20.0);
    }
}

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
    return color * reflectionCoefficient / M_PI;
}

ColorDouble Surface::specularReflection() const {
    return color;
}

double Surface::getReflectionCoefficient() const {
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

const ColorDouble &Surface::getColor() const {
    return hasReflectionModel(SPECULAR) ? ColorDouble(0.0) : color;
}

const ColorDouble &Surface::getEmission() const {
    return emission;
}

