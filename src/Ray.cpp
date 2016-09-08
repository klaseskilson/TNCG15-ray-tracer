#include "Ray.h"

Ray::Ray() {
    this->end = glm::vec3(0.0);
    this->start = glm::vec3(0.0);
}

Ray::Ray(glm::vec3 start, glm::vec3 end) {
    this->end = end;
    this->start = start;
}
