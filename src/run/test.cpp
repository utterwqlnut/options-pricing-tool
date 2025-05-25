#include "../models/black_scholes.h"
#include "../api/api.h"
#include <iostream>
int main() {
    StockTimeSeries sts(10,"AAPL");
    BlackScholes bs(31.55,22.75,0.05,3.5,0.5,true);
    std::cout<<bs.get_price()<<"\n";
}