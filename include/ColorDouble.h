#ifndef TNCG15_COLORDOUBLE_H
#define TNCG15_COLORDOUBLE_H

#include <glm/vec3.hpp>

typedef glm::vec3 ColorDouble;

class ColorDouble : glm::vec3 {
public:
    void getRgb(unsigned char colorArray[]);
};

#endif //TNCG15_COLORDOUBLE_H
