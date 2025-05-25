#include <cmath>
#include "math.h"
#include <iostream>

double ncdf(double val, double mean, double std) {
    double z = (val-mean)/std;
    return (0.5)*(std::erf(z/std::sqrt(2))+1);
}