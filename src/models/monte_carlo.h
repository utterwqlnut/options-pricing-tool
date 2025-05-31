#include "base.h"
#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

double accept_reject_sampling();

class MonteCarlo : public Base{
    private:
        double r;
        double s;
        double t;
        double delta_t;
        double sigma;
        bool call;
        int paths;
        double price;
        double k;

        double next(double curr_s);

    public:
        MonteCarlo(double s,double r,double t,double sigma,bool call,double delta_t, int paths, double k);

        double get_price() const;
};
#endif