#ifndef TNCG15_PIXEL_H
#define TNCG15_PIXEL_H

#include <memory>
#include <list>
#include "ColorDouble.h"
#include "Ray.h"

class Pixel {
public:
    Pixel(ColorDouble colorDouble = ColorDouble());
    void addRay(Ray&);
    const ColorDouble &getColorDouble() const;
private:
    std::list<Ray> rayList;
    ColorDouble colorDouble;
};


#endif //TNCG15_PIXEL_H
