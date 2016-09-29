#ifndef TNCG15_RAY_H
#define TNCG15_RAY_H

#include <glm/glm.hpp>
#include "ColorDouble.h"

class Ray {
public:
    Ray();
    Ray(glm::vec3 start, glm::vec3 end);
    ~Ray() {};
    glm::vec3 returnStartRay() {return start;};
    glm::vec3 returnEndRay() {return end;};
    glm::vec3 getDirection() {return direction;};
private:
    glm::vec3 start, end;
    glm::vec3 direction;
    ColorDouble color;
};

#endif //TNCG15_RAY_H
