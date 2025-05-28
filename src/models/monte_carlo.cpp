#include <cmath>
#include "../helpers/math.h"
#include "black_scholes.h"
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> u_dis(0.0, 1.0);
std::uniform_real_distribution<> h_dis(PDF::min_range, PDF::max_range);

double accept_reject_sampling() {
    double mu,z;
    while(true) {
        // Draw candidate
        mu = u_dis(gen);
        z = h_dis(gen);

        if(mu<=PDF::monte_carlo_pdf(z)/PDF::max_density) {
            return z;
        }
    }
}
