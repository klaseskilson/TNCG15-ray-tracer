#include "utilities.h"

double uniformRand() {
    return DISTR(GENERATOR);
}

double randMinMax(const double &min, const double &max) {
    return min + uniformRand() * (max - min);
}

std::ostream &operator<< (std::ostream &out, const vec3 &vec) {
    out << "{"
        << vec.x << " " << vec.y << " "<< vec.z
        << "}";

    return out;
}
