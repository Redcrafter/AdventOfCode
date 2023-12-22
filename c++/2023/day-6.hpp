#pragma once
#include <array>
#include <cmath>
#include <tuple>

#include "../util.hpp"

namespace y2023::Day6 {

const auto input = readFile("../data/2023/day6.txt");

#define solve(ftype) 2u * (uint32_t)(0.5f * (std::sqrt((ftype)(time * time - 4 * dist - 4)) + time)) + 1 - time;

auto parse() {
    std::array<uint32_t, 4> times;
    std::array<uint32_t, 4> dists;

    for (size_t i = 0; i < 4; i++) {
        auto v1 = *(uint16_t*)(input.data() + 13 + i * 7);
        auto _time = ((v1 & 0xF) * 10) + ((v1 >> 8) & 0xF);

        auto v2 = *(uint32_t*)(input.data() + 48 + i * 7);
        auto _dist = ((v2 & 0xF) * 1000) + (((v2 >> 8) & 0xF) * 100) + (((v2 >> 16) & 0xF) * 10) + ((v2 >> 24) & 0xF);

        times[i] = _time;
        dists[i] = _dist;
    }
    return std::tuple(times, dists);
}

uint64_t part1() {
    const auto [times, dists] = parse();
    uint64_t result = 1;
    for (size_t i = 0; i < 4; i++) {
        auto time = times[i];
        auto dist = dists[i];
        result *= solve(float);
    }
    return result;
}

uint64_t part2() {
    const auto [times, dists] = parse();
    int64_t time = 0;
    int64_t dist = 0;
    for (size_t i = 0; i < 4; i++) {
        time = time * 100 + times[i];
        dist = dist * 10000 + dists[i];
    }
    return solve(double);
}

uint64_t part2_dumb() {
    const auto [times, dists] = parse();
    int64_t time = 0;
    int64_t dist = 0;
    for (size_t i = 0; i < 4; i++) {
        time = time * 100 + times[i];
        dist = dist * 10000 + dists[i];
    }

    int count = 0;
    for (size_t i = 1; i < time; i++) {
        count += i * (time - i) > dist;
    }
    return count;
}

#undef solve

}  // namespace y2023::Day6
