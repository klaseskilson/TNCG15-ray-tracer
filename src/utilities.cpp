#include "utilities.h"

double uniformRand() {
    return DISTR(GENERATOR);
}

std::ostream &operator<< (std::ostream &out, const vec3 &vec) {
    out << "{"
        << vec.x << " " << vec.y << " "<< vec.z
        << "}";

    return out;
}
