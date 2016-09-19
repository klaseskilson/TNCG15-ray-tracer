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
int Triangle::intersection(Ray& ray, glm::vec3 &intersection) {
    // TODO: implement Möller-Trumbore
    glm::vec3 edge1{0.0f, 0.0f, 0.0f};
    glm::vec3 edge2{0.0f, 0.0f, 0.0f};
    glm::vec3 edgeNormal{0.0f, 0.0f, 0.0f};
    glm::vec3 Q{0.0f, 0.0f, 0.0f};
    glm::vec3 distance;

    float determinant = 0.0f;
    float inverted_determinant = 0.0f;
    float T = 0.0f;
    float U = 0.0f;
    float V = 0.0f;

    glm::vec3 endRay = glm::normalize(ray.returnEndRay());
    glm::vec3 startRay = glm::normalize(ray.returnStartRay());
    glm::vec3 direction = endRay - startRay;

    edge1 = positions[1] - positions[0];
    edge2 = positions[2] - positions[0];

    edgeNormal = glm::cross(direction, edge2);
    determinant = dot(edge1, edgeNormal);

    if (std::abs(determinant) < EPSILON)
        return NOT_INTERSECTION;

    inverted_determinant = 1.0f / determinant;

    // calculate distance from first vertex to ray origin
    distance = ray.returnStartRay() - positions[0];

    U = dot(distance, edgeNormal) * inverted_determinant;

    if (U < 0.f || U > 1.f)
        return NOT_INTERSECTION;

    Q = glm::cross(distance, edge1);

    V = dot(endRay, Q) * inverted_determinant;

    if (V < 0.f || U + V  > 1.f)
        return NOT_INTERSECTION;

    T = dot(edge2, Q) * determinant;
    if (T > EPSILON) {
        intersection = distance;
        return INTERSECTION;
    }

    return NOT_INTERSECTION;
}

float Triangle::dot(const glm::vec3 &a, const glm::vec3 &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}