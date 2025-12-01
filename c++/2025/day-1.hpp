#pragma once
#include <array>
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2025::Day1 {

const auto input = aoc::getInput(2025, 1);

uint64_t part1() {
    size_t pos = 0;
    int dial = 50;
    int count = 0;

    while(pos < input.size()) {
        auto dir = input[pos++];
        auto v = readUInt4(input, pos);

        dial += dir == 'R' ? v : -v;
        count += (dial % 100) == 0;
    }

    return count;
}

uint64_t part2() {
    size_t pos = 0;
    int dial = 50;
    int count = 0;

    while(pos < input.size()) {
        auto dir = input[pos++];
        auto v = readUInt4(input, pos);

        if(dir == 'R') {
            count += (dial + v) / 100;
            dial = (dial + v) % 100;
        } else {
            count += ((100 - dial) % 100 + v) / 100;
            dial = (dial - v + 1000) % 100;
        }
    }
    return count;
}

static auto p1 = aoc::test(part1, 2025, 1, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 1, 2, "part2");

} // namespace y2025::Day1
