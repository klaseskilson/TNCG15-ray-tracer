#ifndef TNCG15_BOX_H
#define TNCG15_BOX_H

#include <vector>
#include <glm/gtx/rotate_vector.hpp>
#include "Triangle.h"

class Box {
public:
    Box(glm::vec3 position, float length);

    const std::vector<Triangle> &getTriangles() const;

private:
    std::vector<Triangle> triangles;

};


#endif //TNCG15_BOX_H
