#ifndef TNCG15_SURFACE_H
#define TNCG15_SURFACE_H

#include <iostream>
#include "Ray.h"
#include <glm/glm.hpp>

const int LAMBERTIAN = 0;
const int SPECULAR = 1;
const int LIGHTSOURCE = 2;

class Surface {
public:
    Surface(const ColorDouble &color = ColorDouble(0.0), const int &model = LAMBERTIAN) : color(color), reflectionModel(model) {}

    float getReflectionCoefficient() const;

    const ColorDouble &getColor() const;

    ColorDouble reflect(const Ray &in, const Ray &out, const Direction &normal) const;
    Ray bounceRay(const Ray &in, const vec3 &position, const Direction &normal) const;

    bool hasReflectionModel(const int &model) const {
        return model == reflectionModel;
    }

private:
    ColorDouble color;
    int reflectionModel;
    float reflectionCoefficient = 0.8f;

    // reflection models
    ColorDouble lambertianReflection() const;
    ColorDouble specularReflection() const;
};

#endif //TNCG15_SURFACE_H
