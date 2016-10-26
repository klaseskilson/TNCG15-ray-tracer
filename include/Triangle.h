#ifndef TNCG15_TRIANGLE_H
#define TNCG15_TRIANGLE_H

#define EPSILON 0.00000000000000001

#include <array>
#include <glm/vec3.hpp>
#include "Ray.h"
#include "definitions.h"
#include "Surface.h"
#include "SceneObject.h"

const int INTERSECTION = 1;
const int NOT_INTERSECTION = 0;

class Triangle : public SceneObject {
public:
    Triangle() : Triangle(glm::vec3(), glm::vec3(), glm::vec3()) {};
    Triangle(const glm::vec3&, const glm::vec3&, const glm::vec3&, const Surface &s = Surface());
    int intersection(Ray&, glm::vec3&);
    const glm::vec3 &getNormal() const;

private:
    std::array<glm::vec3, 3> positions;
    glm::vec3 normal;
    glm::vec3 edge1() { return positions[1] - positions[0]; }
    glm::vec3 edge2() { return positions[2] - positions[0]; }
};

#endif //TNCG15_TRIANGLE_H
