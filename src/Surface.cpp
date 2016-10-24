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
    // dE = cos(theta) L dw
    // dL =
    // fr = dL(w0)/dE(wi)
    //
    // diffuse:
    // L = fr * pi
    return color * (double)reflectionCoefficient / M_PI;
}
