#pragma once
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2025::Day7 {

const auto input = aoc::getInput(2025, 7);

uint64_t part1() {
    uint64_t res = 0;

    auto width = input.find_first_of('\n');
    auto height = input.length() / width;
    std::vector<uint8_t> visited(width);

    auto cx = input.find_first_of('S');
    visited[cx] = 1;

    for(size_t y = 2; y < height; y += 2) {
        auto l = cx - (y - 2) / 2;
        auto r = cx + (y - 2) / 2;
        for(size_t x = l; x <= r; x += 2) {
            if(input[x + y * (width + 1)] == '^') {
                res += visited[x];
                visited[x - 1] |= visited[x];
                visited[x + 1] |= visited[x];
                visited[x] = 0;
            }
        }
    }

    return res;
}

uint64_t part2() {
    auto width = input.find_first_of('\n');
    auto height = input.length() / width;
    std::vector<uint64_t> visited(width);

    auto cx = input.find_first_of('S');
    visited[cx] = 1;

    for(size_t y = 2; y < height; y += 2) {
        auto l = cx - (y - 2) / 2;
        auto r = cx + (y - 2) / 2;
        for(size_t x = l; x <= r; x += 2) {
            if(input[x + y * (width + 1)] == '^') {
                visited[x - 1] += visited[x];
                visited[x + 1] += visited[x];
                visited[x] = 0;
            }
        }
    }

    return sum<uint64_t, uint64_t>(visited);
}

static auto p1 = aoc::test(part1, 2025, 7, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 7, 2, "part2");

} // namespace y2025::Day7
