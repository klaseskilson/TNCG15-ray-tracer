#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#include <array>
#include <glm/glm.hpp>
#include "Ray.h"
#include "ColorDouble.h"
#include "Direction.h"

class Triangle {
public:
    Triangle(std::array<glm::vec3, 3> positions) {
        this->positions = positions;
    }
    glm::vec3 *intersection(Ray&);

private:
    std::array<glm::vec3, 3> positions;
    ColorDouble color;
    Direction normal;
};

#endif //TNCG15_TRIANGLE_H
