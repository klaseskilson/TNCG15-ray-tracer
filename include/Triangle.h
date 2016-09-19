#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#include <array>
#include <glm/glm.hpp>
#include "Ray.h"
#include "ColorDouble.h"
#include "Direction.h"

const int INTERSECTION = 1;
const int NOT_INTERSECTION = 0;

class Triangle {
public:
    Triangle(std::array<glm::vec3, 3> positions) {
        this->positions = positions;
    }
    Triangle(glm::vec3&, glm::vec3&, glm::vec3&);
    int intersection(Ray&, glm::vec3&);

private:
    std::array<glm::vec3, 3> positions;
    ColorDouble color;
    Direction normal;
    float dot(const glm::vec3&, const glm::vec3&);
};

#endif //TNCG15_TRIANGLE_H
