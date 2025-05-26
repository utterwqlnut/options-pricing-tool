test: run/test.cpp models/black_scholes.cpp helpers/math.cpp api/api.cpp
	clang++ run/test.cpp models/black_scholes.cpp helpers/math.cpp api/api.cpp -o test -std=c++17 -I/usr/local/include -L/usr/local/lib -I/opt/homebrew/include -L/opt/homebrew/lib -lcpr -lcurl -lmatplot -Wl,-rpath,/usr/local/lib

clean:
	rm -f test