# Options Pricing Tool
> This project is an options pricing tool, meant to provide visualizations and options pricing data through black scholes and other pricing models.
> To get stock time series data, the alpha vantage api is used, and for visualizations we use Matplotplusplus.
> Required External Libraries: [https://github.com/nlohmann/json], [https://github.com/alandefreitas/matplotplusplus], [https://github.com/libcpr/cpr]

## Black Scholes Model
Defined as $C=N(d_1)S-N(d_2)Ke^{-rt}$ and $P=C-S+K*e^{-rt}$. 
With $d_1=\frac{\ln{\frac{S}{K}}+(r+\sigma^2/2)t}{\sigma\sqrt(t)}$ and $d_2=d_1-\sigma\sqrt{t}$
We use historical volatility of user-defined window $w$ for implied volatility.

<img width="1366" alt="Screenshot 2025-05-27 at 4 52 14 PM" src="https://github.com/user-attachments/assets/93fd335b-7295-46a0-a86c-61f52dbff6b6" />

> Here is a generated visualization for AAPL stock.

## Monte Carlo Model (TODO)
Numerical technique to approximate option price by simulating many possible stock paths. Unlike typical monte carlo methods which follow the geometric brownian motion, this model will sample from a user-defined probability distribution during the wiener process. This makes the model more generalizable and applicable to different market scenarios.

$$dS=\mu S_t dt + \sigma S_t dW_t$$
$$dW_t = \sqrt{dt}Z$$
