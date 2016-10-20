#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

ColorDouble Pixel::castRay(Scene &scene) {
    std::list<Triangle> triangles = scene.detectIntersections(rayList[0]);
    // this is wrong, do not use every triangle that is hit!
    for (Triangle &t : triangles) {
        colorDouble += t.getColor();
        // TODO: remove this break, use proper way of collecting colors from collisions
        break;
    }
    return colorDouble;
}

const ColorDouble &Pixel::getColorDouble() const {
    return colorDouble;
}

void Pixel::addRay(Ray &r) {
    rayList.push_back(r);
}
