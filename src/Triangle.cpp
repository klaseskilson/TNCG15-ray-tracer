#include "Triangle.h"
#define EPSILON 0.00000000000000001

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

    float T = 0;
    float determinant = 0;
    float inverted_determinant = 0;
    float U = 0;
    float V = 0;

    glm::vec3 endRay = glm::normalize(ray.returnEndRay());
    glm::vec3 startRay = glm::normalize(ray.returnStartRay());

    e1 = std::get<1>(positions) - std::get<0>(positions);
    e2 = std::get<2>(positions) - std::get<0>(positions);

    P = glm::cross(endRay, e2);

    determinant = (e1.x*P.x)+(e1.y*P.y)+(e1.z+P.z);



    if (determinant > -EPSILON && determinant < EPSILON)
        return nullptr;

    inverted_determinant = 1.0f / determinant;

    T = glm::distance(ray.returnStartRay(),std::get<0>(positions));

    U = glm::dot(T, P) * inverted_determinant;

    if(U < 0.f || U > 1.f)
        return nullptr;

    Q = glm::cross(T, e1);

    V = glm::dot(endRay, Q) * inverted_determinant;

    if(V < 0.f || U + V  > 1.f)
        return nullptr;

    T = glm::dot(e2, Q) * determinant;

    if(T > EPSILON) {
        return T;
    }




    return nullptr;
}