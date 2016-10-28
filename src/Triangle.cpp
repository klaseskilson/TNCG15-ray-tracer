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
    // positions of the ray
    glm::vec3 rayStart = ray.getStart();
    glm::vec3 direction = glm::normalize(ray.getDirection());

    // edges of triangle
    glm::vec3 edge1 = this->edge1();
    glm::vec3 edge2 = this->edge2();

    // calculate determinant
    vec3 edgeNormal = glm::cross(direction, edge2);
    double determinant = glm::dot(edge1, edgeNormal);

    // if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
    if (std::abs(determinant) < EPSILON)
        return NOT_INTERSECTION;

    double inverted_determinant = 1.0 / determinant;

    // calculate rayToVertex from first vertex to ray origin
    vec3 rayToVertex = rayStart - positions[0];

    // Calculate u parameter and test bound, if less than 0 or greater than 1,
    // intersection lies outside of the triangle.
    double U = glm::dot(rayToVertex, edgeNormal) * inverted_determinant;
    if (U < 0.f || U > 1.f)
        return NOT_INTERSECTION;

    // Prepare to test v parameter
    vec3 Q = glm::cross(rayToVertex, edge1);
    // Calculate V parameter and test bound
    double V = glm::dot(direction, Q) * inverted_determinant;
    // The intersection lies outside of the triangle
    if (V < 0.f || U + V  > 1.f)
        return NOT_INTERSECTION;

    double T = glm::dot(edge2, Q) * inverted_determinant;
    if (T > EPSILON) {
        intersection = rayToVertex * (float) T;
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
    double triangleArea = area();
    double a = randMinMax(0.0, 1.0 / triangleArea), b = randMinMax(0.0, 1.0 / triangleArea);
    if (a + b > 1.0) {
        return getRandomPoint();
    }
    return fromBarycentric((float) a, (float) b);
}

vec3 Triangle::fromBarycentric(float a, float b) const {
    vec3 pos = (1.0f - a - b) * positions[0] + a * positions[1] + b * positions[2];
    return pos;
}

double Triangle::area() const {
    return 0.5 * glm::length(glm::cross(edge1(), edge2()));
}
