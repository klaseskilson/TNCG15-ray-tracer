#ifndef TNCG15_UTILS_H
#define TNCG15_UTILS_H

#include <random>
#include "definitions.h"

static std::default_random_engine GENERATOR;
static std::uniform_real_distribution<double> DISTR(0.0, 1.0);

double uniformRand();
std::ostream &operator<< (std::ostream &out, const vec3 &vec);

//double randMinMax(double min, double max) {
//    std::uniform_real_distribution<double> dist(min, max);
//    return dist(GENERATOR);
//}

#endif //TNCG15_UTILS_H
