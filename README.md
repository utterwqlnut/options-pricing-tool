# Options Pricing Tool
> This project is an options pricing tool, meant to provide visualizations and options pricing data through black scholes and other pricing models.
> To get stock time series data, the alpha vantage api is used, and for visualizations we use Matplotplusplus.
> Required External Libraries: [https://github.com/nlohmann/json], [https://github.com/alandefreitas/matplotplusplus], [https://github.com/libcpr/cpr]

## Black Scholes Model (Done)
Defined as $C=N(d_1)S-N(d_2)Ke^{-rt}$ and $P=C-S+K*e^{-rt}$. 
With $d_1=\frac{\ln{\frac{S}{K}}+(r+\sigma^2/2)t}{\sigma\sqrt(t)}$ and $d_2=d_1-\sigma\sqrt{t}$
We use historical volatility of user-defined window $w$ for implied volatility.

<img width="1366" alt="Screenshot 2025-05-27 at 4 52 14 PM" src="https://github.com/user-attachments/assets/93fd335b-7295-46a0-a86c-61f52dbff6b6" />

> Here is a generated visualization for AAPL stock.

## Monte Carlo Model (TODO)
Numerical technique to approximate option price by simulating many possible stock paths. Unlike typical monte carlo methods which follow the geometric brownian motion, this model will sample from a user-defined probability distribution during the wiener process. This makes the model more generalizable and applicable to different market scenarios.

### Wiener Process (TODO)
$$dS=\mu S_t dt + \sigma S_t dW_t$$

$$dW_t = \sqrt{dt} \cdot Z$$

Typically $Z \sim N(0,1)$ however in our model Z samples from the user defined distribution.

### Sampling (Done)
Because we need to support a variety of probability distributions, we will be using accept-reject sampling.

Suppose we have an uknown distribution $f(x)$ we wish to sample from. We then use a proposal distribution $h(x)$ (In our case it is a uniform distribution) which is easier to sample from and acts as a container around $f(x)$, 
meaning there is some constant c such that $f(x) \leq ch(x)$.

The algorithm then follows

1. Draw candidate $z$ from $h(x)$ and $\mu$ from $U(0,1)$
2. If $\mu \leq \frac{f(z)}{ch(z)}$ than $z$ is a valid draw, otherwise go back to 1.
