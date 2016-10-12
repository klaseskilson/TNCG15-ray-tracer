//
// Created by Carl Englund on 2016-10-12.
//

#ifndef TNCG15_BOX_H
#define TNCG15_BOX_H

#include "Triangle.h"

class Box {
public:
    void createBox();
private:
    std::array<Triangle, 12> triangles;

};


#endif //TNCG15_BOX_H
