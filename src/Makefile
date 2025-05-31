run: run/run.cpp models/black_scholes.cpp models/monte_carlo.cpp helpers/math.cpp api/api.cpp models/base.cpp
	clang++ run/run.cpp models/base.cpp models/monte_carlo.cpp models/black_scholes.cpp helpers/math.cpp api/api.cpp -o run_script -std=c++17 -I/usr/local/include -L/usr/local/lib -I/opt/homebrew/include -L/opt/homebrew/lib -lcpr -lcurl -lmatplot -Wl,-rpath,/usr/local/lib

clean:
	rm -f run_script