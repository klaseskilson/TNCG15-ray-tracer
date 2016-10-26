#include "Triangle.h"

Triangle::Triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const Surface &s) {
    positions[0] = a;
    positions[1] = b;
    positions[2] = c;
    surface = s;

    // set normal
    normal = glm::normalize(glm::cross(edge1(), edge2()));
}

/**
 * find intersection of ray and triangle using Möller-Trumbore
 * @param ray
 * @param intersection the returned intersection, if found.
 * @return INTERSECTION if found, NOT_INTERSECTION otherwise
 */
int Triangle::intersection(Ray& ray, glm::vec3 &intersection) {
    glm::vec3 edgeNormal{0.0f, 0.0f, 0.0f};
    glm::vec3 Q{0.0f, 0.0f, 0.0f};
    glm::vec3 distance;

    float determinant = 0.0f;
    float inverted_determinant = 0.0f;
    float T = 0.0f;
    float U = 0.0f;
    float V = 0.0f;

    // positions of the ray
    glm::vec3 rayStart = glm::normalize(ray.getStart());
    glm::vec3 direction = glm::normalize(ray.getDirection());
    glm::vec3 endRay = rayStart + direction;

    // edges of triangle
    glm::vec3 edge1 = positions[1] - positions[0];
    glm::vec3 edge2 = positions[2] - positions[0];

    // calculate determinant
    edgeNormal = glm::cross(direction, edge2);
    determinant = glm::dot(edge1, edgeNormal);

    // if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
    if (std::abs(determinant) < EPSILON)
        return NOT_INTERSECTION;

    inverted_determinant = 1.0f / determinant;

    // calculate distance from first vertex to ray origin
    distance = rayStart - positions[0];

    // Calculate u parameter and test bound, if less than 0 or greater than 1,
    // intersection lies outside of the triangle.
    U = glm::dot(distance, edgeNormal) * inverted_determinant;
    if (U < 0.f || U > 1.f)
        return NOT_INTERSECTION;

    // Prepare to test v parameter
    Q = glm::cross(distance, edge1);
    // Calculate V parameter and test bound
    V = glm::dot(direction, Q) * inverted_determinant;
    // The intersection lies outside of the triangle
    if (V < 0.f || U + V  > 1.f)
        return NOT_INTERSECTION;

    T = glm::dot(edge2, Q) * inverted_determinant;
    if (T > EPSILON) {
        intersection = distance;
        return INTERSECTION;
    }

    return NOT_INTERSECTION;
}

const glm::vec3 &Triangle::getNormal() const {
    return normal;
}

const Surface &Triangle::getSurface() const {
    return surface;
}

vec3 Triangle::getRandomPoint() const {
    double a = uniformRand(), b = uniformRand();
    if (a + b > 1.0) {
        return getRandomPoint();
    }
    return fromBarycentric((float) a, (float) b);
}

vec3 Triangle::fromBarycentric(float a, float b) const {
    return (1.0f - a - b) * positions[0] + a * positions[1] + b * positions[2];
}