#pragma once
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2025::Day4 {

const auto input = aoc::getInput(2025, 4);

const auto height = 139;
const auto width = 139;

auto make_grid() {
    Grid<width + 2, height + 2, char> grid; // 1 space padding

    for(size_t y = 0; y < width + 2; y++) {
        grid(y, 0) = 0;
        grid(y, height + 1) = 0;
        grid(0, y) = 0;
        grid(width + 1, y) = 0;
    }
    for(size_t y = 0; y < 139; y++) {
        for(size_t x = 0; x < 139; x++) {
            grid(x + 1, y + 1) = input[x + y * (width + 1)] == '@';
        }
    }
    return grid;
}

uint64_t part1() {
    auto grid = make_grid();

    uint64_t res = 0;
    for(int y = 1; y < height + 1; y++) {
        for(int x = 1; x < width + 1; x++) {
            auto c = grid(x, y);
            if(c == 0) continue;

            auto tl = grid(x - 1, y - 1);
            auto t  = grid(x + 0, y - 1);
            auto tr = grid(x + 1, y - 1);

            auto l = grid(x - 1, y + 0);
            auto r = grid(x + 1, y + 0);

            auto bl = grid(x - 1, y + 1);
            auto b  = grid(x + 0, y + 1);
            auto br = grid(x + 1, y + 1);

            if(tl + t + tr + l + r + bl + b + br < 4)
                res++;
        }
    }
    return res;
}

uint64_t part2() {
    uint64_t res = 0;

    auto grid = make_grid();

    std::vector<std::pair<int, int>> changed;
    std::vector<std::pair<int, int>> next;

    auto test = [&](int x, int y) {
        auto c = grid(x, y);
        if(c == 0) return;

        auto tl = grid(x - 1, y - 1);
        auto t  = grid(x + 0, y - 1);
        auto tr = grid(x + 1, y - 1);

        auto l = grid(x - 1, y + 0);
        auto r = grid(x + 1, y + 0);

        auto bl = grid(x - 1, y + 1);
        auto b  = grid(x + 0, y + 1);
        auto br = grid(x + 1, y + 1);

        if(tl + t + tr + l + r + bl + b + br < 4) {
            changed.emplace_back(x, y);
            grid(x, y) = 0;
            res++;
        }
    };

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            test(x + 1, y + 1);
        }
    }

    while(changed.size() > 0) {
        std::swap(next, changed);
        changed.clear();
        for(auto& [x, y] : next) {
            test(x - 1, y - 1);
            test(x + 0, y - 1);
            test(x + 1, y - 1);
            test(x - 1, y);
            test(x + 1, y);
            test(x - 1, y + 1);
            test(x + 0, y + 1);
            test(x + 1, y + 1);
        }
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 4, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 4, 2, "part2");

} // namespace y2025::Day4
