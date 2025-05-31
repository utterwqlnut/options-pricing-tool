#include "base.h"
#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

class BlackScholes : public Base{
    private:
        double s;
        double k;
        double r;
        double t;
        double sigma;
        bool call;
        double price;

        double call_price();

        double put_price();

    public:
        BlackScholes(double s,double k,double r,double t,double sigma,bool call);
        
        double get_price() const;

};

#endif