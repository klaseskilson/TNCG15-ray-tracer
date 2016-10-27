#ifndef TNCG15_UTILS_H
#define TNCG15_UTILS_H

#include <random>
#include "definitions.h"

static std::default_random_engine GENERATOR;
static std::uniform_real_distribution<double> DISTR(0.0, 1.0);

double uniformRand();
double randMinMax(const double &min, const double &max);


std::ostream &operator<< (std::ostream &out, const vec3 &vec);


#endif //TNCG15_UTILS_H
