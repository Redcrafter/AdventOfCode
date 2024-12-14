#pragma once

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day13 {

auto parseFast() {
    auto inp = aoc::getInput(2024, 13);
    std::vector<double> nums;

    for(size_t i = 0; i < inp.size();) {
        nums.push_back(readExactInt<double, 2>(inp, i + 12));
        nums.push_back(readExactInt<double, 2>(inp, i + 18));
        nums.push_back(readExactInt<double, 2>(inp, i + 33));
        nums.push_back(readExactInt<double, 2>(inp, i + 39));
        i += 51;
        nums.push_back(readUInt<double>(inp, i));
        i += 3;
        nums.push_back(readUInt<double>(inp, i));
        i++;
    }

    return nums;
}

const auto input = parseFast();

double calc(double ax, double ay, double bx, double by, double px, double py) {
    auto det = ax * by - bx * ay;

    auto ac = (px * by - py * bx) / det;
    auto bc = (py * ax - px * ay) / det;

    if(ac != std::floor(ac) || bc != std::floor(bc)) return 0;
    return 3 * ac + bc;
}

uint64_t part1() {
    double result = 0;
    for(int i = 0; i < input.size(); i += 6) {
        result += calc(input[i + 0], input[i + 1],
                       input[i + 2], input[i + 3],
                       input[i + 4], input[i + 5]);
    }
    return result;
}

uint64_t part2() {
    double result = 0;
    for(int i = 0; i < input.size(); i += 6) {
        result += calc(input[i + 0], input[i + 1],
                       input[i + 2], input[i + 3],
                       input[i + 4] + 10000000000000.0, input[i + 5] + 10000000000000.0);
    }
    return result;
}

static auto p = aoc::test([]() {
    auto input = extractNumbers<int>(aoc::getInput(2024, 13));
    return input.size();
}, 2024, 13, 0, "parse");

static auto pf = aoc::test([]() {
    auto input = parseFast();
    return input.size();
}, 2024, 13, 0, "parse fast");

static auto p1 = aoc::test(part1, 2024, 13, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 13, 2, "part 2");

} // namespace y2024::Day13
