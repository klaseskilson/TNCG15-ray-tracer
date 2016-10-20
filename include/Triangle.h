#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#define EPSILON 0.00000000000000001

#include <array>
#include <glm/vec3.hpp>
#include "Ray.h"
#include "definitions.h"

const int INTERSECTION = 1;
const int NOT_INTERSECTION = 0;

class Triangle {
public:
    Triangle() : Triangle(glm::vec3(), glm::vec3(), glm::vec3()) {};
    Triangle(const std::array<glm::vec3, 3> p) : Triangle(p[0], p[1], p[2], color) {};
    Triangle(const glm::vec3&, const glm::vec3&, const glm::vec3&, const ColorDouble &color = ColorDouble(0.0f));
    int intersection(Ray&, glm::vec3&);
    int sphereIntersection(Ray&, glm::vec3&);

    const ColorDouble &getColor() const;

private:
    std::array<glm::vec3, 3> positions;
    ColorDouble color;
    Direction normal;
};

#endif //TNCG15_TRIANGLE_H
