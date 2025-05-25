#include <string>

#ifndef API_H
#define API_H


void test_api_connection();

std::string get_daily_json(std::string ticker);

class StockTimeSeries {
    private:
        double *prices;
        int deltat;
        std::string ticker;
    public:
        StockTimeSeries(int deltat, std::string ticker);
        double* get_prices();
};

#endif