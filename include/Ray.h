#ifndef TNCG15_RAY_H
#define TNCG15_RAY_H

#include <glm::vec3>

class Ray {
public:
    Ray();
    Ray(glm::vec3 start, glm::vec3 end);
private:
    glm::vec3 start, end;
    ColourDouble color;
};

#endif //TNCG15_RAY_H
