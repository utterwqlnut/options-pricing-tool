#include <cmath>
#include "math.h"
#include <iostream>

double ncdf(double val, double mean, double std) {
    double z = (val-mean)/std;
    return (0.5)*(std::erf(z/std::sqrt(2))+1);
}

// User fill this out
const double PDF::max_density = 1.0 / (std::sqrt(2 * M_PI));
const double PDF::min_range = -3;
const double PDF::max_range = 3;

double PDF::monte_carlo_pdf(double val) {
    // User fill this in default is normal pdf
    return (1.0 / (std::sqrt(2 * M_PI))) *
            std::exp(-0.5 * std::pow(val, 2));
}