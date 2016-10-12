#include "Ray.h"

Ray::Ray() {
    start = glm::vec3(0.0);
    direction = glm::vec3(0.0);
}

Ray::Ray(glm::vec3 s, glm::vec3 d) {
    start = s;
    direction = d;
}
