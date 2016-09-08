#include "ColorDouble.h"

void ColorDouble::getRgb(unsigned char colorArray[]) {
    colorArray[0] = (this->r * 256);
    colorArray[1] = (this->g * 256);
    colorArray[2] = (this->b * 256);
}