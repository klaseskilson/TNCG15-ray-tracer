#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#include <array>
#include <glm/vec3.hpp>
#include "Ray.h"

class Triangle {
public:
    Triangle(std::array<glm::vec3, 3> positions) {
        this->positions = positions;
    }
    glm::vec3 intersection(Ray);
private:
    std::array<glm::vec3, 3> positions;
};

#endif //TNCG15_TRIANGLE_H
