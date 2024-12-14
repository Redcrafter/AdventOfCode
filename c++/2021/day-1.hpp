#pragma once
#include "../aoc.hpp"
#include "../util.hpp"

namespace y2021::Day1 {

const auto input = extractNumbers<uint16_t>(aoc::getInput(2021, 1));

uint64_t part1() {
    int count = 0;
    for(int i = 1; i < input.size(); i++) {
        count += input[i] > input[i - 1];
    }
    return count;
}

uint64_t part2() {
    int count = 0;
    for(int i = 3; i < input.size(); i++) {
        int last = input[i - 3] + input[i - 2] + input[i - 1];
        int current = input[i - 2] + input[i - 1] + input[i];
        count += current > last;
    }
    return count;
}

static auto p1 = aoc::test(part1, 2021, 1, 1, "part1");
static auto p2 = aoc::test(part2, 2021, 1, 2, "part2");

} // namespace y2021::Day1
