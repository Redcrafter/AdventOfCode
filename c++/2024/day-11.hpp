#pragma once
#include <array>
#include <ranges>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day11 {

const auto nums = extractNumbers<int>(aoc::getInput(2024, 11));

uint64_t ipow(int base, int exp) {
    uint64_t result = 1;
    while(exp != 0) {
        if((exp & 1) == 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

class CustomMap {
  public:
    std::array<std::pair<int64_t, uint64_t>, 5003> data; // size is prime
    std::vector<int> used;

    void clear() {
        data.fill({-1, 0});
        used.clear();
    }
    uint64_t& operator[](uint64_t i) {
        auto x = (i * 0x45d9f3b) % data.size();

        while(true) {
            auto& v = data[x];

            if(v.first == i) {
                return v.second;
            }
            if(v.first == -1) {
                v.first = i;
                used.push_back(x);
                return v.second;
            }
            x = (x + 1) % data.size();
        }
    }
};

uint64_t solve(int n) {
    CustomMap curr{}, next;

    curr.clear();
    next.clear();

    for(auto&& i : nums) {
        curr[i] = 1;
    }

    for(int i = 0; i < n; i++) {
        for(auto id : curr.used) {
            auto [s, count] = curr.data[id];
            curr.data[id] = {-1, 0};

            if(s == 0) {
                next[1] += count;
            } else {
                auto len = (int)std::log10(s) + 1;
                if(len % 2 == 0) {
                    len = ipow(10, len / 2);
                    next[(s / len)] += count;
                    next[s % len] += count;
                } else {
                    next[s * 2024] += count;
                }
            }
        }
        curr.used.clear();

        std::swap(curr, next);
    }

    uint64_t result = 0;
    for(auto [s, count] : curr.data) {
        if(s < 0) continue;

        result += count;
    }
    return result;
}

static auto p = aoc::test([]() {
    auto input = extractNumbers<int>(aoc::getInput(2024, 11));
    return input.size();
}, 2024, 11, 0, "parse");
static auto p1 = aoc::test([]() { return solve(25); }, 2024, 11, 1, "part 1");
static auto p2 = aoc::test([]() { return solve(75); }, 2024, 11, 2, "part 2");

} // namespace y2024::Day11
