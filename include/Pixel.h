#ifndef TNCG15_PIXEL_H
#define TNCG15_PIXEL_H

#include "ColorDouble.h"

class Pixel {
public:
    Pixel(ColorDouble colorDouble = ColorDouble());
    void addRay(Ray &ray);
private:
    std::list<std::unique_ptr<Ray>> rayList;
    ColorDouble colorDouble;
};


#endif //TNCG15_PIXEL_H
