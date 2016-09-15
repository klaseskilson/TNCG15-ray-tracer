#include "Scene.h"
#include "Triangle.h"

void Scene::createScene() {
    //Create some triangles that form the room
	//Floor
	std::array<glm::vec3, 3> floor {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f)};	
	std::array<glm::vec3, 3> floor {glm::vec3(0.0f, 6.0f, -5.0f),glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f)};	
	std::array<glm::vec3, 3> floor {glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(0.0f, 6.0f, -5.0f)};	
	std::array<glm::vec3, 3> floor {glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(10.0f, 6.0f, -5.0f)};	
	//Right side back
	std::array<glm::vec3, 3> rightSideBack {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Left Side back
	std::array<glm::vec3, 3> leftSideBack {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Left Side front
	std::array<glm::vec3, 3> leftSideFront {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Right Side front
	std::array<glm::vec3, 3> rightSideFront {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Front
	std::array<glm::vec3, 3> backSide {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Back
	std::array<glm::vec3, 3> frontSide {glm::vec3( 10, 0, 0),glm::vec3( 10, 0, 0), glm::vec3( 10, 0, 0)};	
	//Floor
	Triangle floorTriangles {floor};
	//Roof
	//Walls
	
}

std::list<Triangle> Scene::detectIntersections(Ray ray) {
    std::list<Triangle> intersections = {};
    for (Triangle t : this->triangles) {
        glm::vec3 *intersection = t.intersection(ray);
        if (intersection != nullptr) {
            // intersection found, add it to some sort of list etc
            intersections.push_back(t);
        }
    }
    return intersections;
};
