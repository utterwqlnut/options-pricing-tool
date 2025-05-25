#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

class BlackScholes {
    private:
        double s;
        double k;
        double r;
        double t;
        double sigma;
        bool call;
        double price;

    public:
        BlackScholes(double s,double k,double r,double t,double sigma,bool call);

        double call_price();

        double put_price();

        double get_price() const;
};

#endif