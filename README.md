# AdventOfCode

## Usage
### Js (node & deno)
To download inputs and print results enter your session token in `js/api.js` and then run `node js/test.js` \
run a benchmark with `node js/benchmark.js` \
run individual days using `node js/{year}/{day}.js`

### C++
Place your inputs into `data/year/dayX.txt`

Compile `c++/main.cpp` using your favorite compiler e.g.
```
cd c++/
wget https://raw.githubusercontent.com/nlohmann/json/refs/heads/master/single_include/nlohmann/json.hpp
clang++ -std=c++23 -O3 -march=native ./main.cpp
./a.out
```
