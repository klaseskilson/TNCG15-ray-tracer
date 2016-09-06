#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDouble) {
    this.colorDouble = colorDouble;
}

Pixel::addRay(Ray &ray) {
    this.rayList.push_back(std::unique_ptr(ray));
}
