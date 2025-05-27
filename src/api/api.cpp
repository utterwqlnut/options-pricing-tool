#include <cpr/cpr.h>
#include "api.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <nlohmann/json.hpp>
#include <typeinfo>
#include <cmath>
using json = nlohmann::json;


typedef struct Time{
    int hour;
    int minute;
    int second;
} Time;

std::string get_daily_json(std::string ticker) {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol="+ticker+"&interval=5min&apikey=GGFXUHYGT68UN2XC"});
    if (r.status_code != 200) {
        return "Invalid Ticker";
    } else {
        return r.text;
    }
}

void test_api_connection() {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=GGFXUHYGT68UN2XC"});
    std::cout<<"Status Code\n"<<r.status_code<<"\n";
    std::cout<<"Body\n"<<r.text<<"\n";
}


StockTimeSeries::StockTimeSeries(int deltat, std::string ticker) : deltat(deltat), ticker(ticker)  {
    prices = (double*) std::malloc(sizeof(double)*deltat);
    double* log_returns = (double*) std::malloc(sizeof(double)*(deltat-1));
    json data = json::parse(get_daily_json(ticker))["Time Series (Daily)"];
    
    int count = 0;
    for (auto it=data.rbegin(); it!=data.rend(); it++) {
        if(count==deltat) {
            break;
        }
        *(prices+count) = std::stod((*it)["4. close"].dump().substr(1,-1));
        count++;
    }

    for (int i=0;i<deltat-1;i++) {
        *(log_returns+i) = std::log(*(prices+i)/(*(prices+i+1)));
    }

    double sum = 0;
    for (int i=0;i<deltat-1;i++) {
        sum+=*(log_returns+i);
    }
    double mean = sum/(deltat-1);

    double sum_diff_sq = 0;
    for (int i=0;i<deltat-1;i++) {
        sum_diff_sq+=(*(log_returns+i)-mean)*(*(log_returns+i)-mean);
    }

    historical_iv = std::sqrt(sum_diff_sq/(deltat-2))*std::sqrt(252);
    
}

double* StockTimeSeries::get_prices() {
    return prices;
}
double StockTimeSeries::get_historical_iv() {
    return historical_iv;
}