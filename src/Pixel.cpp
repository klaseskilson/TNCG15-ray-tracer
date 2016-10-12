#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

void Pixel::setRay(Ray &r) {
    ray = r;
}

ColorDouble Pixel::getColorDouble(Scene &scene) {
    std::list<Triangle> t = scene.detectIntersections(ray);
    if (t.size() > 0) {
        colorDouble += t.front().getColor();
    }
    return colorDouble;
}

Ray Pixel::getRay() {
    return ray;
}
