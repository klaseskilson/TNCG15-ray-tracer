#ifndef TNCG15_PIXEL_H
#define TNCG15_PIXEL_H

#include <memory>
#include <list>
#include "definitions.h"
#include "Ray.h"
#include "Scene.h"

class Pixel {
public:
    Pixel(ColorDouble colorDouble = ColorDouble(0.0f));
    ColorDouble castRay(Scene &);
    void addRay(Ray &);

    const ColorDouble &getColorDouble() const;

private:
    std::vector<Ray> rayList;
    ColorDouble colorDouble;
};


#endif //TNCG15_PIXEL_H
