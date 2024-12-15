#pragma once
#include <array>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day14 {

const auto input = extractNumbers<int8_t, true>(aoc::getInput(2024, 14));
const int width = 101;
const int height = 103;

uint64_t part1() {
    int tl = 0;
    int tr = 0;
    int bl = 0;
    int br = 0;

    for(int i = 0; i < input.size(); i += 4) {
        auto px = input[i];
        auto py = input[i + 1];
        auto vx = input[i + 2];
        auto vy = input[i + 3];

        px = (((px + vx * 100) % width) + width) % width;
        py = (((py + vy * 100) % height) + height) % height;

        if(px < 50 && py < 51) tl++;
        if(px > 50 && py < 51) tr++;
        if(px < 50 && py > 51) bl++;
        if(px > 50 && py > 51) br++;
    }
    return tl * tr * bl * br;
}

template<bool overlap>
uint64_t part2_brute() {
    std::array<uint8_t, width * height> grid;

    for(int i = 1;; i++) {
        grid.fill(0);

        for(int j = 0; j < input.size(); j += 4) {
            auto px = input[j];
            auto py = input[j + 1];
            auto vx = input[j + 2];
            auto vy = input[j + 3];

            px = (((px + vx * i) % width) + width) % width;
            py = (((py + vy * i) % height) + height) % height;

            grid[px + py * width]++;
        }

        if constexpr(overlap) {
            bool valid = true;
            for(int j = 0; j < grid.size(); j++) {
                if(grid[j] == 2) valid = false;
            }
            if(valid) return i;
        } else {
            for(int j = 0; j + 15 < grid.size(); j += 15) {
                bool valid = true;
                for(int k = 0; k < 15; k++) {
                    if(grid[j + k] == 0) valid = false;
                }
                if(valid) return i;
            }
        }
    }
}

uint64_t part2_crt() {
    std::array<uint8_t, 103> arr1;
    std::array<uint8_t, 103> arr2;

    auto mod_w = std::pair(-1, 1 << 30);
    auto mod_h = std::pair(-1, 1 << 30);
    for(int i = 0; i < width; i++) {
        arr1.fill(0);
        arr2.fill(0);

        for(int j = 0; j < input.size(); j += 4) {
            auto px = input[j];
            auto py = input[j + 1];
            auto vx = input[j + 2];
            auto vy = input[j + 3];

            arr1[(((px + vx * i) % width) + width) % width] = 1;
            arr2[(((py + vy * i) % height) + height) % height] = 1;
        }

        int sum1 = 0;
        int sum2 = 0;
        for(int j = 0; j < 103; j++) {
            sum1 += arr1[j];
            sum2 += arr2[j];
        }
        if(sum1 < mod_w.second) mod_w = {i, sum1};
        if(sum2 < mod_h.second) mod_h = {i, sum2};
    }

    return ((mod_w.first * height + mod_h.first * width) * 51) % (width * height);
}

static auto p = aoc::test([]() {
    return extractNumbers<int8_t, true>(aoc::getInput(2024, 14)).size();
}, 2024, 14, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 14, 1, "part 1");
static auto p2bc = aoc::test(part2_brute<false>, 2024, 14, 2, "part 2 brute chain");
static auto p2bo = aoc::test(part2_brute<true>, 2024, 14, 2, "part 2 brute overlap");
static auto p2c = aoc::test(part2_crt, 2024, 14, 2, "part 2 crt");

} // namespace y2024::Day14
