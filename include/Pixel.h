#ifndef TNCG15_PIXEL_H
#define TNCG15_PIXEL_H

#include <memory>
#include <list>
#include <glm/gtx/vector_angle.hpp>
#include "definitions.h"
#include "Ray.h"
#include "Scene.h"

class Pixel {
public:
    Pixel(ColorDouble colorDouble = ColorDouble(0.0f));

    void setColorDouble(const ColorDouble &colorDouble);

    void addRay(Ray &);

    const ColorDouble &getColorDouble() const;

    const std::vector<Ray> &getRayList() const;

    Ray getFirstRay();

private:
    std::vector<Ray> rayList;
    ColorDouble colorDouble;
};


#endif //TNCG15_PIXEL_H
