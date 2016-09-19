#include "Scene.h"
#include "Triangle.h"

void Scene::createScene() {
    //Create some triangles that form the room
	//Floor
	std::array<glm::vec3, 3> floor1 {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f)};	
	std::array<glm::vec3, 3> floor2 {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f)};	
	std::array<glm::vec3, 3> floor3 {glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(0.0f, 6.0f, -5.0f)};	
	std::array<glm::vec3, 3> floor4 {glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(10.0f, 6.0f, -5.0f)};	
	//Roof
	std::array<glm::vec3, 3> roof1 {glm::vec3(0.0f, 6.0f, 5.0f),glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(10.0f, -6.0f, 5.0f)};	
	std::array<glm::vec3, 3> roof2 {glm::vec3(0.0f, 6.0f, 5.0f),glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(10.0f, 6.0f, 5.0f)};	
	std::array<glm::vec3, 3> roof3 {glm::vec3(-3.0f, 0.0f, 5.0f), glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(0.0f, 6.0f, 5.0f)};	
	std::array<glm::vec3, 3> roof4 {glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(13.0f, 0.0f, 5.0f), glm::vec3(10.0f, 6.0f, 5.0f)};
	//Right side back
	std::array<glm::vec3, 3> rightSideBack1 {glm::vec3(10.0f, 6.0f, -5.0f),glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(13.0f, 0.0f, 5.0f)};	
	std::array<glm::vec3, 3> rightSideBack2 {glm::vec3(13.0f, 0.0f, 5.0f),glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(10.0f, 6.0f, -5.0f)};	
	std::array<glm::vec3, 3> rightSideBack3 {glm::vec3(13.0f, 0.0f, 5.0f),glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(13.0f, 0.0f, 5.0f)};	
	std::array<glm::vec3, 3> rightSideBack4 {glm::vec3(13.0f, 0.0f, -5.0f),glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, 5.0f)};	
	//Left Side back
	std::array<glm::vec3, 3> leftSideBack1 {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(0.0f, 6.0f, 5.0f), glm::vec3(-3.0f, 0.0f, 5.0f)};	
	std::array<glm::vec3, 3> leftSideBack2 {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(-3.0f, 0.0f, 5.0f), glm::vec3(-3.0f, 0.0f, -5.0f)};	
	std::array<glm::vec3, 3> leftSideBack3 {glm::vec3(-3.0f, 0.0f, -5.0f),glm::vec3(-3.0f, 0.0f, 5.0f), glm::vec3(0.0f, -6.0f, 5.0f)};	
	std::array<glm::vec3, 3> leftSideBack4 {glm::vec3(-3.0f, 0.0f, -5.0f),glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(0.0f, -6.0f, -5.0f)};	
	//Left Side front
	std::array<glm::vec3, 3> WallFront1 {glm::vec3(0.0f, -6.0f, -5.0f),glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(0.0f, -6.0f, 5.0f)};	
	std::array<glm::vec3, 3> WallFront2 {glm::vec3(10.0f, -6.0f, -5.0f),glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(0.0f, -6.0f, 5.0f)};	

	std::array<glm::vec3, 3> WallBack1 {glm::vec3(0.0f, 6.0f, 5.0f),glm::vec3(10.0f, 6.0f, -5.0f), glm::vec3(0.0f, 6.0f, 5.0f)};	
	std::array<glm::vec3, 3> WallBack2 {glm::vec3(10.0f, 6.0f, -5.0f),glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(0.0f, 6.0f, 5.0f)};	

	
	//Triangle floorTriangles {floor};

	
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
