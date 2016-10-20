#ifndef TNCG15_RAY_H
#define TNCG15_RAY_H

#include "definitions.h"
#include <glm/glm.hpp>

class Ray {
public:
    Ray();
    Ray(glm::vec3 start, glm::vec3 direction);
    ~Ray() {};
    glm::vec3 getStart() {return start;};
    glm::vec3 getDirection() {return direction;};
private:
    glm::vec3 start, direction;
    ColorDouble color = ColorDouble(0.0f);
};

#endif //TNCG15_RAY_H
