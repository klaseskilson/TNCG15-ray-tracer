#ifndef TNCG15_RAY_H
#define TNCG15_RAY_H

#include "definitions.h"
#include <glm/glm.hpp>

class Ray {
public:
    Ray() : Ray(vec3(0.0f), vec3(0.0f)) {};
    Ray(vec3 start, vec3 direction);
    Ray bounce(const vec3 &position, const vec3 &normal) const;
    ~Ray() {};
    vec3 getStart() const {return start;};
    vec3 getDirection() const {return direction;};

    void setColor(const ColorDouble &color);

private:
    vec3 start, direction;
    ColorDouble color = ColorDouble(0.0f);
};

#endif //TNCG15_RAY_H
