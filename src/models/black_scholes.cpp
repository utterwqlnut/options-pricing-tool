#include <cmath>
#include "../helpers/math.h"
#include "black_scholes.h"
#include <iostream>

    BlackScholes::BlackScholes(double s,double k,double r,double t,double sigma,bool call) : s(s), k(k), r(r), t(t), sigma(sigma), call(call) {
        if (call) {
            price = call_price();
        } else {
            price = put_price();
        }
    }

    double BlackScholes::call_price() {
        double d1 = (std::log(s/k) + (r+sigma*sigma/2)*t)/(sigma*std::sqrt(t));
        double d2 = d1-sigma*std::sqrt(t);
        return ncdf(d1,0,1)*s-ncdf(d2,0,1)*k*std::exp(-r*t);
    }

    double BlackScholes::put_price() {
        return k*std::exp(-r*t)-s+call_price();
    }

    double BlackScholes::get_price() const {
        return price;
    }