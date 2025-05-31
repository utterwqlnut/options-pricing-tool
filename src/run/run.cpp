#include "../models/black_scholes.h"
#include "../api/api.h"
#include <iostream>
#include <matplot/matplot.h>
#include <fstream>
#include <string>
#include "../models/monte_carlo.h"

int main() {
    std::string ticker;
    double annualized_interest_rate;
    int iv_window;
    bool call;
    int max_day;
    int min_day;
    int res;
    std::string model;
    int paths;
    double delta_t;

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

    std::cout<<"Which model eg. \"black_scholes\" or \"monte_carlo\""<<"\n";
    std::cin>>model;


    if(!model.compare("monte_carlo")) {
        std::cout<<"How many paths to evaluate"<<"\n";
        std::cin>>paths;

        std::cout<<"What is the delta_t for the mc"<<"\n";
        std::cin>>delta_t;

    }

    StockTimeSeries sts(iv_window,ticker);

    std::vector<std::vector<double> > option_surface_X;
    std::vector<std::vector<double> > option_surface_Y;
    std::vector<std::vector<double> > option_surface_Z;
    std::vector<std::vector<double> > option_surface_data;

    Base* calc;

    // LinSpace from min_day to max_day
    for(double day=min_day;day<=max_day;day+=(max_day-min_day)/(double)(res-1)) {
        double upper_price = *(sts.get_prices())+0.5*(*(sts.get_prices()));
        double lower_price = *(sts.get_prices())-0.5*(*(sts.get_prices()));
        std::vector<double> v_x;
        std::vector<double> v_y;
        std::vector<double> v_z;
        // LinSpace from lower_price to upper_price
        for(double strike=lower_price;strike<=upper_price;strike+=(upper_price-lower_price)/(res-1)) {
            if(strike!=lower_price) {
                delete calc;
            }
            if(!model.compare("monte_carlo")) {
                calc = new MonteCarlo(*(sts.get_prices()),annualized_interest_rate,day/365.0,sts.get_historical_iv(),call,delta_t/365.0, paths, strike);
            } else {
                calc = new BlackScholes(*(sts.get_prices()),strike,annualized_interest_rate,day/365.0,sts.get_historical_iv(),call);
            }
            v_y.push_back(strike);
            v_x.push_back(day);
            v_z.push_back(calc->get_price());
            option_surface_data.push_back({day,strike,calc->get_price()});
        }
        option_surface_X.push_back(v_x);
        option_surface_Y.push_back(v_y);
        option_surface_Z.push_back(v_z);
    }

    // Graph surface
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

    std::cout << "Press ENTER to exit and save data to data.txt" << std::endl;
    std::cin.get();

    // Output data to file
    std::ofstream datafile;
    datafile.open("data.txt");
    for(int i=0;i<option_surface_data.size();i++) {
        datafile<<"Days till Expiration: "<<option_surface_data[i][0]<<" Strike Price "<<option_surface_data[i][1]<<" Option Price "<<option_surface_data[i][2]<<"\n";
    }
    datafile.close();

    return 0;
}