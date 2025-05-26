#include "../models/black_scholes.h"
#include "../api/api.h"
#include <iostream>
#include <matplot/matplot.h>

int main() {
    std::string ticker;
    double annualized_interest_rate;
    int iv_window;
    bool call;
    int max_day;
    int min_day;
    int res;

    // Get Inputs

    std::cout<<"Enter ticker symbol"<<"\n";
    std::cin>>ticker;

    std::cout<<"Enter annualized interest rate"<<"\n";
    std::cin>>annualized_interest_rate;

    std::cout<<"Enter historical IV window"<<"\n";
    std::cin>>iv_window;

    std::cout<<"Enter 1 for call 0 for put"<<"\n";
    std::cin>>call;

    std::cout<<"Enter max day for visualization"<<"\n";
    std::cin>>max_day;

    std::cout<<"Enter min day for visualization"<<"\n";
    std::cin>>min_day;

    std::cout<<"Enter resolution for visualization"<<"\n";
    std::cin>>res;

    StockTimeSeries sts(iv_window,"AAPL");

    // X,Y,Z grids

    std::vector<std::vector<double> > option_surface_X;
    std::vector<std::vector<double> > option_surface_Y;
    std::vector<std::vector<double> > option_surface_Z;

    // LinSpace from min_day to max_day
    for(double day=min_day;day<=max_day;day+=(max_day-min_day)/(double)(res-1)) {
        double upper_price = *(sts.get_prices())+0.5*(*(sts.get_prices()));
        double lower_price = *(sts.get_prices())-0.5*(*(sts.get_prices()));
        // X,Y,Z rows
        std::vector<double> v_x;
        std::vector<double> v_y;
        std::vector<double> v_z;

        // LinSpace from lower_price to upper_price
        for(double strike=lower_price;strike<=upper_price;strike+=(upper_price-lower_price)/(res-1)) {

            BlackScholes calc(*(sts.get_prices()),strike,annualized_interest_rate,day/365.0,sts.get_historical_iv(),call);
            v_y.push_back(strike);
            v_x.push_back(day);
            v_z.push_back(calc.get_price());
            break;
        }
        option_surface_X.push_back(v_x);
        option_surface_Y.push_back(v_y);
        option_surface_Z.push_back(v_z);
    }
    auto l = matplot::surf(option_surface_X, option_surface_Y, option_surface_Z);
    matplot::xlabel("Days till Expiration");
    matplot::ylabel("Strike Price");
    matplot::zlabel("Option Price");
    if (call) {
        matplot::view(120, 30);
    } else {
        matplot::view(60, 30);
    }
    matplot::show();

    std::cout << "Press ENTER to exit..." << std::endl;
    std::cin.get();
}