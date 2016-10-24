#include "Surface.h"

ColorDouble Surface::reflect(const Ray &in, const Ray &out) const {
    switch (reflectionModel) {
        case LAMBERTIAN:
            return lambertianReflection();
        default:
            std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
            return ColorDouble(0.0);
    }
}

ColorDouble Surface::lambertianReflection() const {
    return color * (double)reflectionCoefficient / M_PI;
}

float Surface::getReflectionCoefficient() const {
    return reflectionCoefficient;
}
