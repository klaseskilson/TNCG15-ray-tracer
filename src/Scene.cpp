//
// Created by Carl Englund on 06/09/16.
//

#include "Scene.h"

void Scene::createScene() {
    //Create some triangles that form the room
}

std::list<Triangle> Scene::detectIntersections(Ray ray) {
    std::list<Triangle> intersections = {};
    for (Triangle t : this->triangles) {
        glm::vec3 intersection = t.intersection(ray);
        if (intersection != Ray::NotFound) {
            // intersection found, add it to some sort of list etc
            intersections.push_back(t);
        }
    }
    return intersections;
};