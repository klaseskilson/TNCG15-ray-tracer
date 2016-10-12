//
// Created by Carl Englund on 2016-10-12.
//

#ifndef TNCG15_BOX_H
#define TNCG15_BOX_H

#include <vector>
#include "Triangle.h"

class Box {
public:
    void createBox(glm::vec3 position, float length);
private:
    std::vector<Triangle> triangles;

};


#endif //TNCG15_BOX_H
