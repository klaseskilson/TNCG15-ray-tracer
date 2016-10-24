#include "Scene.h"
#include <glm/gtx/rotate_vector.hpp>

Scene::Scene() {
    createBox(glm::vec3(0.0f, -2.0f, 5.0f), 2);
    createRoom();
    Sphere sphere(glm::vec3(-2.0f, 2.0f, 7.0f), 1.0f, ColorDouble(0.0f, 1.0f, 0.0f));
    spheres.push_back(sphere);
}

void Scene::createRoom() {
// View from above:
// ^ = camera 1 and viewing direction (origo)
// v = camera 2 and viewing direction
//           a
//          / \   <-- front
// LEFT    b v c     RIGHT
//         |   |  <-- center
//         d ^ e
//          \ /   <-- back
//           f
//
//    ^ z
//    |
//    |----> x

    glm::vec3 aBottom(0.0f, -5.0f, 13.0f), aTop(0.0f, 5.0f, 13.0f);
    glm::vec3 bBottom(-6.0f, -5.0f, 10.0f), bTop(-6.0f, 5.0f, 10.0f);
    glm::vec3 cBottom(6.0f, -5.0f, 10.0f), cTop(6.0f, 5.0f, 10.0f);
    glm::vec3 dBottom(-6.0f, -5.0f, 0.0f), dTop(-6.0f, 5.0f, 0.0f);
    glm::vec3 eBottom(6.0f, -5.0f, 0.0f), eTop(6.0f, 5.0f, 0.0f);
    glm::vec3 fBottom(0.0f, -5.0f, -3.0f), fTop(0.0f, 5.0f, -3.0f);

    const Surface White(ColorDouble(1.0f));
    const Surface Grey(ColorDouble(0.5f));
    const Surface Red(ColorDouble(1.0f, 0.0f, 0.0f));
    const Surface Green(ColorDouble(0.0f, 1.0f, 0.0f));
    const Surface Blue(ColorDouble(0.0f, 0.0f, 1.0f));
    const Surface Yellow(ColorDouble(1.0f, 1.0f, 0.0f));
    const Surface Purple(ColorDouble(1.0f, 0.0f, 1.0f));
    const Surface Teal(ColorDouble(0.0f, 1.0f, 1.0f));

    // Floor
    triangles.push_back(Triangle(bBottom, cBottom, aBottom, White));
    triangles.push_back(Triangle(bBottom, dBottom, cBottom, White));
    triangles.push_back(Triangle(dBottom, eBottom, cBottom, White));
    triangles.push_back(Triangle(dBottom, fBottom, eBottom, White));
    // Roof
    triangles.push_back(Triangle(bTop, aTop, cTop, Grey));
    triangles.push_back(Triangle(bTop, cTop, dTop, Grey));
    triangles.push_back(Triangle(dTop, cTop, eTop, Grey));
    triangles.push_back(Triangle(dTop, eTop, fTop, Grey));
    // Right side back
    triangles.push_back(Triangle(fBottom, fTop, eTop, Blue));
    triangles.push_back(Triangle(fBottom, eTop, eBottom, Blue));
    // Left side back
    triangles.push_back(Triangle(dBottom, dTop, fTop, Yellow));
    triangles.push_back(Triangle(dBottom, fTop, fBottom, Yellow));
    // Left side center
    triangles.push_back(Triangle(bBottom, bTop, dTop, Yellow));
    triangles.push_back(Triangle(bBottom, dTop, dBottom, Yellow));
    // Left side front
    triangles.push_back(Triangle(aBottom, aTop, bTop, Purple));
    triangles.push_back(Triangle(aBottom, bTop, bBottom, Purple));
    // Right side front
    triangles.push_back(Triangle(cBottom, cTop, aTop, Purple));
    triangles.push_back(Triangle(cBottom, aTop, aBottom, Purple));
    // Right side center
    triangles.push_back(Triangle(eBottom, eTop, cTop, Blue));
    triangles.push_back(Triangle(eBottom, cTop, cBottom, Blue));
}

void Scene::createBox(glm::vec3 position, float length) {
    glm::vec3 frontUpperRight(position.x+length, position.y+length, position.z+length),
              frontBottomRight(position.x+length, position.y, position.z+length);
    glm::vec3 frontBottomLeft(position.x, position.y, position.z+length),
              frontUpperLeft(position.x, position.y+length, position.z+length);
    glm::vec3 backUpperLeft(position.x, position.y+length, position.z+length),
              backUpperRight(position.x+length, position.y, position.z+(length*2));
    glm::vec3 backBottomRight(position.x+length, position.y, position.z+(length)),
              backBottomLeft(position.x, position.y, position.z+length);

    frontUpperRight = glm::rotateY(frontUpperRight, (float)M_1_PI/3.f);
    frontBottomRight = glm::rotateY(frontBottomRight, (float)M_1_PI/3.f);
    frontBottomLeft = glm::rotateY(frontBottomLeft, (float)M_1_PI/3.f);
    frontUpperLeft = glm::rotateY(frontUpperLeft, (float)M_1_PI/3.f);

    const Surface Red(ColorDouble(1.0f, 0.0f, 0.0f));
    const Surface Green(ColorDouble(0.0f, 1.0f, 0.0f));
    const Surface Blue(ColorDouble(0.0f, 0.0f, 1.0f));
    const Surface Yellow(ColorDouble(1.0f, 1.0f, 0.0f));
    const Surface Purple(ColorDouble(1.0f, 0.0f, 1.0f));
    const Surface Teal(ColorDouble(0.0f, 1.0f, 1.0f));

    //Box floor
    triangles.push_back(Triangle(frontBottomRight, backBottomRight, frontBottomLeft, Red));
    triangles.push_back(Triangle(frontBottomRight, frontBottomLeft, backBottomLeft, Red));
    //Box Front
    triangles.push_back(Triangle(frontBottomRight, frontUpperRight, frontUpperLeft, Green));
    triangles.push_back(Triangle(frontBottomRight, frontBottomLeft, frontUpperLeft, Green));
    //Box Right Side
    triangles.push_back(Triangle(frontUpperRight, frontBottomRight, backBottomRight, Blue));
    triangles.push_back(Triangle(frontUpperRight, backUpperRight, backBottomRight, Blue));
    //Box Left Side
    triangles.push_back(Triangle(frontUpperLeft, frontBottomLeft, backBottomLeft, Yellow));
    triangles.push_back(Triangle(frontUpperLeft, backUpperLeft, backBottomLeft, Yellow));
    //Box Back Side
    triangles.push_back(Triangle(backBottomRight, backUpperRight, backUpperLeft, Purple));
    triangles.push_back(Triangle(backBottomRight, backBottomLeft, backUpperLeft, Purple));
    //Box Roof
    triangles.push_back(Triangle(frontUpperRight, backUpperRight, backUpperLeft, Teal));
    triangles.push_back(Triangle(frontUpperRight, frontUpperLeft, backUpperLeft, Teal));
}

/**
 * detect ray intersection
 * @param ray
 * @return list of TriangleIntersections, sorted by distance to ray start
 */
std::list<TriangleIntersection> Scene::detectIntersections(Ray ray) {
    std::list<TriangleIntersection> intersections = {};
    for (Triangle triangle : triangles) {
        TriangleIntersection ti;
        glm::vec3 intersection;
        int result = triangle.intersection(ray, intersection);
        if (result == INTERSECTION) {
            // intersection found, add it to the list of intersections
            ti.triangle = triangle;
            ti.point = intersection;
            intersections.push_back(ti);
        }
    }
    vec3 rayStart = ray.getStart();
    intersections.sort([&rayStart](const auto &a, const auto &b) {
        return glm::length(a.point - rayStart) < glm::length(b.point - rayStart);
    });
    return intersections;
};

std::list<Sphere> Scene::detectSphereIntersections(Ray ray) {
    std::list<Sphere> intersectingSpheres = {};
    for(Sphere s : spheres) {
        glm::vec3 intersection;
        int result = s.sphereIntersection(ray, intersection);
        if(result == INTERSECTION) {
            intersectingSpheres.push_back(s);
        }
    }
    return intersectingSpheres;
};
