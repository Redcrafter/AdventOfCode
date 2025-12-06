#pragma once
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2025::Day4 {

const auto input = aoc::getInput(2025, 4);

const auto height = 139;
const auto width = 139;

uint64_t part1() {
    uint64_t res = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto c = input[x + y * (width + 1)];
            if (c != '@') continue;

            auto tl = y > 0 &&          x > 0         && input[x - 1 + (y - 1) * (width + 1)] == '@';
            auto t  = y > 0 &&                           input[x + 0 + (y - 1) * (width + 1)] == '@';
            auto tr = y > 0 &&          x + 1 < width && input[x + 1 + (y - 1) * (width + 1)] == '@';

            auto l  =                   x > 0         && input[x - 1 + (y + 0) * (width + 1)] == '@';
            auto r  =                   x + 1 < width && input[x + 1 + (y + 0) * (width + 1)] == '@';

            auto bl = y + 1 < height && x > 0         && input[x - 1 + (y + 1) * (width + 1)] == '@';
            auto b  = y + 1 < height &&                  input[x + 0 + (y + 1) * (width + 1)] == '@';
            auto br = y + 1 < height && x + 1 < width && input[x + 1 + (y + 1) * (width + 1)] == '@';

            if (tl + t + tr + l + r + bl + b + br < 4)
                res++;
        }
    }

    return res;
}

uint64_t part2() {
    uint64_t res = 0;

    // make copy
    auto inp = std::string(input);

    std::vector<std::pair<int, int>> changed;
    std::vector<std::pair<int, int>> next;

    auto test = [&](int x, int y) {
        auto c = inp[x + y * (width + 1)];
        if (c != '@') return;

        auto tl = y > 0 &&          x > 0         && inp[x - 1 + (y - 1) * (width + 1)] == '@';
        auto t  = y > 0                           && inp[x + 0 + (y - 1) * (width + 1)] == '@';
        auto tr = y > 0 &&          x + 1 < width && inp[x + 1 + (y - 1) * (width + 1)] == '@';

        auto l  =                   x > 0         && inp[x - 1 + (y + 0) * (width + 1)] == '@';
        auto r  =                   x + 1 < width && inp[x + 1 + (y + 0) * (width + 1)] == '@';

        auto bl = y + 1 < height && x > 0         && inp[x - 1 + (y + 1) * (width + 1)] == '@';
        auto b  = y + 1 < height                  && inp[x + 0 + (y + 1) * (width + 1)] == '@';
        auto br = y + 1 < height && x + 1 < width && inp[x + 1 + (y + 1) * (width + 1)] == '@';

        if (tl + t + tr + l + r + bl + b + br < 4) {
            changed.emplace_back(x, y);
            inp[x + y * (width + 1)] = '.';
            res++;
        }
    };

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            test(x, y);
        }
    }

    while (changed.size() > 0) {
        std::swap(next, changed);
        changed.clear();
        for(auto& [x, y] : next) {
            if(y > 0 &&          x > 0        ) test(x - 1, y - 1);
            if(y > 0                          ) test(x + 0, y - 1);
            if(y > 0 &&          x + 1 < width) test(x + 1, y - 1);
            if(                  x > 0        ) test(x - 1, y);
            if(                  x + 1 < width) test(x + 1, y);
            if(y + 1 < height && x > 0        ) test(x - 1, y + 1);
            if(y + 1 < height                 ) test(x + 0, y + 1);
            if(y + 1 < height && x + 1 < width) test(x + 1, y + 1);
        }
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 4, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 4, 2, "part2");

} // namespace y2025::Day3
