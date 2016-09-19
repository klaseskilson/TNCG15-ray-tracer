#include "Triangle.h"
#define EPSILON 0.00000000000000001

Triangle::Triangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c) {
    positions[0] = a;
    positions[1] = b;
    positions[2] = c;
}

/**
 * find intersection of ray and triangle
 * @param ray
 * @return glm::vec3 if found, otherwise null
 */
glm::vec3 *Triangle::intersection(Ray& ray) {
    // TODO: implement Möller-Trumbore
    glm::vec3 e1{0.0f, 0.0f, 0.0f};
    glm::vec3 e2{0.0f, 0.0f, 0.0f};
    glm::vec3 P{0.0f, 0.0f, 0.0f};
    glm::vec3 Q{0.0f, 0.0f, 0.0f};
    glm::vec3 T{0.0f, 0.0f, 0.0f};

    float t = 0;
    float determinant = 0;
    float inverted_determinant = 0;
    float u = 0;
    float v = 0;
    glm::vec3 endRay = glm::normalize(ray.returnEndRay());

    for(auto & this: triangles) {
        e1 = triangle[1] - triangle[0];
        e2 = triangle[2] - triangle[1];

        P = glm::cross(D, e2);
        determinant = glm::dot(e1, P);

        if (determinant > -EPSILON && determinant < EPSILON) continue;

        inverted_determinant = 1.0f / determinant;
        T = O - triangle[0];

        




    }


    return nullptr;
}