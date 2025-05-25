#include "../models/black_scholes.h"
#include "../api/api.h"
#include <iostream>
int main() {
    StockTimeSeries sts(5,"AAPL");
    BlackScholes bs(*(sts.get_prices()),200,0.05,0.014,sts.get_historical_iv(),true);
    std::cout<<bs.get_price()<<"\n";
}