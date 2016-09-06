#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#include <glm::vec3>
#include "Ray.h"

class Triangle {
    Triangle(glm::vec3[] positions) {
        this->positions = positions;
    };
    glm::vec3 instersection(Ray ray);
private:
    glm::vec3[3] positions;
};


#endif //TNCG15_TRIANGLE_H
