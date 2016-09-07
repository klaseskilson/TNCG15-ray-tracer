#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDouble) {
    this->colorDouble = colorDouble;
}

void Pixel::addRay(std::shared_ptr<Ray> ray) {
    this->rayList.push_back(ray);
}
