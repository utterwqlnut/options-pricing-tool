#include <cpr/cpr.h>
#include "api.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <nlohmann/json.hpp>
#include <typeinfo>
using json = nlohmann::json;
// TODO: We need to be able to grab all historical data in an array
// Then in helpers have a historical volatility calculation

typedef struct Time{
    int hour;
    int minute;
    int second;
} Time;

std::string get_daily_json(std::string ticker) {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol="+ticker+"&interval=5min&apikey=PWHH9JPBR0HITP8Y"});
    if (r.status_code != 200) {
        return "Invalid Ticker";
    } else {
        return r.text;
    }
}

void test_api_connection() {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=PWHH9JPBR0HITP8Y"});
    std::cout<<"Status Code\n"<<r.status_code<<"\n";
    std::cout<<"Body\n"<<r.text<<"\n";
}


StockTimeSeries::StockTimeSeries(int deltat, std::string ticker) : deltat(deltat), ticker(ticker)  {
    prices = (double*) std::malloc(sizeof(double)*deltat);
    json data = json::parse(get_daily_json(ticker))["Time Series (Daily)"];
    
    int count = 0;
    for (json::iterator it=data.begin(); it!=data.end(); it++) {
        if(count==deltat) {
            break;
        }
        *(prices+count) = std::stod((*it)["4. close"].dump().substr(1,-1));
        count++;
    }
}

double* StockTimeSeries::get_prices() {
    return prices;
}