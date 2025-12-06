#pragma once
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2025::Day3 {

const auto input = aoc::getInput(2025, 3);

template<int N>
auto findMaxN(std::string_view line) {
    std::array<int, N> temp;
    for(int i = 0; i < N; i++) {
        temp[i] = line[100 - N + i];
    }

    for(int i = 100 - N - 1; i >= 0; i--) {
        auto c = line[i];
        if(c >= temp[0]) {
            auto t = temp[0];
            for (int j = 1; j < N; j++) {
                if(t >= temp[j]) {
                    std::swap(t, temp[j]);
                } else {
                    break;
                }
            }
            temp[0] = c;
        }
    }

    uint64_t res = 0;
    for (size_t i = 0; i < N; i++) {
        res = res * 10 + temp[i] - '0';
    }
    return res;
}

uint64_t part1() {
    uint64_t res = 0;

    for(size_t i = 0; i < 200; i++) {
        auto line = input.substr(i * 101, 100);

        // res += findMaxN<2, char>(line);

        // faster for some reason?
        int max = line[98];
        int next = line[99];

        for(int j = 97; j >= 0; j--) {
            auto c = line[j];
            if(c >= max) {
                if(max >= next)
                    next = max;
                max = c;
            }
        }
        res += (max - '0') * 10 + (next - '0');
    }

    return res;
}

uint64_t part2() {
    uint64_t res = 0;

    for(size_t i = 0; i < 200; i++) {
        auto line = input.substr(i * 101, 100);
        res += findMaxN<12>(line);
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 3, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 3, 2, "part2");

} // namespace y2025::Day3
