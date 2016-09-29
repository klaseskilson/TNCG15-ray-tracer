#include "Scene.h"
#include "Triangle.h"

void Scene::createScene() {
// View from above:
// ^ = camera and viewing direction (origo)
//           a
//          / \   <-- front
// LEFT    b   c     RIGHT
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

	// Floor
	triangles[0] = Triangle(bBottom, cBottom, aBottom);
	triangles[1] = Triangle(bBottom, dBottom, cBottom);
	triangles[2] = Triangle(dBottom, eBottom, cBottom);
	triangles[3] = Triangle(dBottom, fBottom, eBottom);
	// Roof
	triangles[4] = Triangle(bTop, aTop, cTop);
	triangles[5] = Triangle(bTop, cTop, dTop);
	triangles[6] = Triangle(dTop, cTop, eTop);
	triangles[7] = Triangle(dTop, eTop, fTop);
	// Right side back
	triangles[8] = Triangle(fBottom, fTop, eTop);
	triangles[9] = Triangle(fBottom, eTop, eBottom);
	// Left side back
    triangles[10] = Triangle(dBottom, dTop, fTop);
    triangles[11] = Triangle(dBottom, fTop, fBottom);
    // Left side center
    triangles[12] = Triangle(bBottom, bTop, dTop);
    triangles[13] = Triangle(bBottom, dTop, dBottom);
	// Left side front
	triangles[14] = Triangle(aBottom, aTop, bTop);
	triangles[15] = Triangle(aBottom, bTop, bBottom);
    // Right side front
    triangles[16] = Triangle(cBottom, cTop, aTop);
    triangles[17] = Triangle(cBottom, aTop, aBottom);
    // Right side center
    triangles[18] = Triangle(eBottom, eTop, cTop);
    triangles[19] = Triangle(eBottom, cTop, cBottom);
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
