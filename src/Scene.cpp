#include "Scene.h"
#include "Triangle.h"

void Scene::createScene() {
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

    glm::vec3 aBottom(0.0f, 0.0f, 5.0f), aTop(0.0f, 5.0f, 5.0f);
    glm::vec3 bBottom(-2.5f, 0.0f, 2.5f), bTop(-2.5f, 5.0f, 2.5f);
    glm::vec3 cBottom(2.5f, 0.0f, 2.5f), cTop(2.5f, 5.0f, 2.5f);
    glm::vec3 dBottom(-2.5f, 0.0f, 0.0f), dTop(-2.5f, 5.0f, 0.0f);
    glm::vec3 eBottom(2.5f, 0.0f, 0.0f), eTop(2.5f, 5.0f, 0.0f);
    glm::vec3 fBottom(2.5f, 0.0f, -2.5f), fTop(2.5f, 5.0f, -2.5f);

    const ColorDouble Red(255.0f, 0.0f, 0.0f);
    const ColorDouble Green(0.0f, 255.0f, 0.0f);
    const ColorDouble Blue(0.0f, 0.0f, 255.0f);
    const ColorDouble Yellow(255.0f, 255.0f, 0.0f);
    //const ColorDouble Teal(0.0f, 255.0f, 255.0f);
    const ColorDouble Purple(255.0f, 0.0f, 255.0f);

    // Floor
    triangles[0] = Triangle(bBottom, cBottom, aBottom, Red);
    triangles[1] = Triangle(bBottom, dBottom, cBottom, Red);
    triangles[2] = Triangle(dBottom, eBottom, cBottom, Red);
    triangles[3] = Triangle(dBottom, fBottom, eBottom, Red);
    // Roof
    triangles[4] = Triangle(bTop, aTop, cTop, Green);
    triangles[5] = Triangle(bTop, cTop, dTop, Green);
    triangles[6] = Triangle(dTop, cTop, eTop, Green);
    triangles[7] = Triangle(dTop, eTop, fTop, Green);
    // Right side back
    triangles[8] = Triangle(fBottom, fTop, eTop, Blue);
    triangles[9] = Triangle(fBottom, eTop, eBottom, Blue);
    // Left side back
    triangles[10] = Triangle(dBottom, dTop, fTop, Blue);
    triangles[11] = Triangle(dBottom, fTop, fBottom, Blue);
    // Left side center
    triangles[12] = Triangle(bBottom, bTop, dTop, Yellow);
    triangles[13] = Triangle(bBottom, dTop, dBottom, Yellow);
	  // Left side front
	  triangles[14] = Triangle(aBottom, aTop, bTop, Purple);
	  triangles[15] = Triangle(aBottom, bTop, bBottom, Purple);
    // Right side front
    triangles[16] = Triangle(cBottom, cTop, aTop, Purple);
    triangles[17] = Triangle(cBottom, aTop, aBottom, Purple);
    // Right side center
    triangles[18] = Triangle(eBottom, eTop, cTop, Yellow);
    triangles[19] = Triangle(eBottom, cTop, cBottom, Yellow);
}

std::list<Triangle> Scene::detectIntersections(Ray ray) {
    std::list<Triangle> intersectingTriangles = {};
	  std::list<glm::vec3> intersectionVertices = {};
    for (Triangle t : triangles) {
        glm::vec3 intersection;
		    int result = t.intersection(ray, intersection);
        if (result == INTERSECTION) {
            // intersection found, add it to some sort of list etc
            intersectingTriangles.push_back(t);
			      intersectionVertices.push_back(intersection);
        }
    }
    return intersectingTriangles;
};
