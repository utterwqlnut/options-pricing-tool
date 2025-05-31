#include <cmath>
#include "../helpers/math.h"
#include "monte_carlo.h"
#include <iostream>
#include <random>
#include <algorithm>

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

double MonteCarlo::next(double curr_s) {
    //std::cout<<accept_reject_sampling()<<"\n";
    return curr_s+r*curr_s*delta_t+sigma*curr_s*std::sqrt(delta_t)*accept_reject_sampling();
}

MonteCarlo::MonteCarlo(double s,double r,double t,double sigma,bool call,double delta_t, int paths, double k) : s(s), r(r), t(t), sigma(sigma), call(call), delta_t(delta_t), paths(paths), k(k) {  
    double curr_s;
    double sum=0;
    for(int i=0;i<paths;i++) {
        curr_s = s;
        for(double j=delta_t;j<=t;j+=delta_t) {
            curr_s = next(curr_s);
        }
        if(call) {
            sum+=std::exp(-r*t)*(std::max(curr_s-k,0.0));
        } else {
            sum+=std::exp(-r*t)*(std::max(k-curr_s,0.0));
        }
    }
    price = sum/paths;
}

double MonteCarlo::get_price() const {
    return price;
}


