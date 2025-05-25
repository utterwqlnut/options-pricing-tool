#include "../models/black_scholes.h"
#include "../api/api.h"
#include <iostream>

int main() {
    std::string ticker;
    double strike;
    double annualized_interest_rate;
    int days_to_option;
    int iv_window;
    bool call;

    std::cout<<"Enter ticker symbol"<<"\n";
    std::cin>>ticker;

    std::cout<<"Enter strike price"<<"\n";
    std::cin>>strike;

    std::cout<<"Enter annualized interest rate"<<"\n";
    std::cin>>annualized_interest_rate;

    std::cout<<"Enter days till option expiration"<<"\n";
    std::cin>>days_to_option;

    std::cout<<"Enter historical IV window"<<"\n";
    std::cin>>iv_window;

    std::cout<<"Enter 1 for call 0 for put"<<"\n";
    std::cin>>call;

    StockTimeSeries sts(iv_window,"AAPL");
    BlackScholes bs(*(sts.get_prices()),strike,annualized_interest_rate,days_to_option/365.0,sts.get_historical_iv(),call);
    std::cout<<bs.get_price()<<"\n";
}