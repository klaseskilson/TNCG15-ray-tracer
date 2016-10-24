#ifndef TNCG15_SURFACE_H
#define TNCG15_SURFACE_H

#include <iostream>
#include "definitions.h"
#include "Ray.h"

const int LAMBERTIAN = 0;

class Surface {
public:
    Surface(const ColorDouble &color = ColorDouble(0.0)) : color(color) {}

    float getReflectionCoefficient() const;

    ColorDouble reflect(const Ray &in, const Ray &out) const;

private:
    ColorDouble color;
    int reflectionModel = LAMBERTIAN;
    float reflectionCoefficient = 0.8f;

    // reflection models
    ColorDouble lambertianReflection() const;
};

#endif //TNCG15_SURFACE_H
