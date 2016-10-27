#ifndef TNCG15_LIGHT_H
#define TNCG15_LIGHT_H

#include <glm/vec3.hpp>
#include <vector>
#include "definitions.h"
#include "Triangle.h"

class Light {
public:
    Light();
    const std::vector<Triangle> &getTriangles() const;

    double getLightIntensity() const;

private:
    std::vector<Triangle> triangles;
    double lightIntensity = 2.0;
};
#endif //TNCG15_LIGHT_H
