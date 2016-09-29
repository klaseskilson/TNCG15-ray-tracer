//
// Created by Carl Englund on 06/09/16.
//

#ifndef TNCG15_SCENE_H
#define TNCG15_SCENE_H

#include <array>
#include <list>
#include "Triangle.h"
#include "Ray.h"

class Scene {
public:
    //Should probably not be void..
    void createScene();
    std::list<Triangle> detectIntersections(Ray ray);
private:
    std::array<Triangle, 20> triangles;
};


#endif //TNCG15_SCENE_H
