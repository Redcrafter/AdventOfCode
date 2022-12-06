#pragma once
#include <array>
#include <cctype>

#include "../util.hpp"

namespace y2022::Day6 {

std::array<uint8_t, 4095> parseData() {
    std::array<uint8_t, 4095> data{};
    auto line = readLines("../data/2022/day6.txt")[0];

    for (size_t i = 0; i < 4095; i++) {
        data[i] = line[i] - 'a';
    }

    return data;
}

auto input = parseData();

uint64_t part1() {
    int i = 0;
    while (true) {
        auto d = input[i + 3];
        auto c = input[i + 2];
        if (d == c) {
            i += 3;
            continue;
        }

        auto b = input[i + 1];
        if (d == b || c == b) {
            i += 2;
            continue;
        }

        auto a = input[i];
        if (d == a || c == a || b == a) {
            i += 1;
            continue;
        }

        return i + 4;
    }
}

uint64_t part2() {
    int i = 0;
    while (true) {
    loop:
#pragma unroll
        for (int j = 12; j >= 0; j--) {
#pragma unroll
            for (int k = j + 1; k <= 13; k++) {
                if (input[i + j] == input[i + k]) {
                    i += j + 1;
                    goto loop;

                }
            }
        }

        return i + 14;
    }
}

}  // namespace y2022::Day6
