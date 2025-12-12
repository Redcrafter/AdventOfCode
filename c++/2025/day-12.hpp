#pragma once
#include <unordered_map>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2025::Day12 {

const auto input = aoc::getInput(2025, 12);

uint64_t part1() {
    size_t pos = 96;

    int res = 0;
    while(pos < input.size()) {
        auto w = readExactInt<int, 2>(input.substr(pos));
        auto h = readExactInt<int, 2>(input.substr(pos + 3));
        pos += 7;

        int sum = 0;
        for (size_t i = 0; i < 6; i++) {
            sum += readExactInt<int, 2>(input.substr(pos));
            pos += 3;
        }
        
        res += (w / 3) * (h / 3) >= sum;
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 12, 1, "part1");

} // namespace y2025::Day12
