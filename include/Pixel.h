#ifndef TNCG15_PIXEL_H
#define TNCG15_PIXEL_H

#include <memory>
#include <list>
#include "ColorDouble.h"
#include "Ray.h"

class Pixel {
public:
    Pixel(ColorDouble colorDouble = ColorDouble());
    void addRay(std::shared_ptr<Ray>);
private:
    std::list<std::shared_ptr<Ray>> rayList;
    ColorDouble colorDouble;
};


#endif //TNCG15_PIXEL_H
