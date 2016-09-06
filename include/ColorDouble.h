#ifndef TNCG15_COLORDOUBLE_H
#define TNCG15_COLORDOUBLE_H

#include <glm/vec4.hpp>

class ColorDouble {
public:
    ColorDouble() : ColorDouble(0.0) {};
    ColorDouble(double value) : ColorDouble(glm::vec4((float) value)) {};
    ColorDouble(glm::vec4 color) {
        this->color = color;
    };
    glm::vec4 getColor() {
        return this->color;
    };
private:
    glm::vec4 color;
};

#endif //TNCG15_COLORDOUBLE_H
