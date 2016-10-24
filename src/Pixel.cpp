#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

const ColorDouble &Pixel::getColorDouble() const {
    return colorDouble;
}

void Pixel::addRay(Ray &r) {
    rayList.push_back(r);
}

Ray Pixel::getFirstRay() {
    return rayList[0];
}

void Pixel::setColorDouble(const ColorDouble &colorDouble) {
    Pixel::colorDouble = colorDouble;
}
