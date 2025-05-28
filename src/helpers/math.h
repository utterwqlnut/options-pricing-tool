#ifndef MATH_H
#define MATH_H


double ncdf(double val, double mean, double std);

class PDF {
    public:
        static const double max_density;
        static const double min_range;
        static const double max_range;
        static double monte_carlo_pdf(double val);
};

#endif