#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

ColorDouble Pixel::castRay(Scene &scene) {
    std::list<Triangle> t = scene.detectIntersections(rayList[0]);
    if (t.size() > 0) {
        colorDouble += t.front().getColor();
    }
    return colorDouble;
}

const ColorDouble &Pixel::getColorDouble() const {
    return colorDouble;
}

void Pixel::addRay(Ray &r) {
    rayList.push_back(r);
}
