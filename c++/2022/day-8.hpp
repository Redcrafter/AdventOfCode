#pragma once
#include "../grid.hpp"
#include "../util.hpp"

namespace y2022::Day8 {

auto parseInput() {
    auto lines = readLines("../data/2022/day8.txt");

    Grid<99, 99, uint8_t> dat{};
    for (size_t y = 0; y < lines.size(); y++) {
        auto line = lines[y];
        for (size_t x = 0; x < line.size(); x++) {
            dat(x, y) = line[x] - '0';
        }
    }

    return dat;
}

auto input = parseInput();

uint64_t part1() {
    Grid<99, 99, bool> visited{};

    const auto size = 99;
    int count = 0;

    auto ray = [&]<int dx, int dy>(int x, int y) {
        int height = -1;

        while (height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            int v = input(x, y);
            if (v > height) {
                height = v;
                count += visited(x, y) == 0;
                visited(x, y) = true;
            }

            x += dx;
            y += dy;
        }
    };

    for (int i = 0; i < size; i++) {
        ray.operator()<1, 0>(0, i);
        ray.operator()<-1, 0>(98, i);
        ray.operator()<0, 1>(i, 0);
        ray.operator()<0, -1>(i, 98);
    }

    return count;
}

uint64_t part2() {
    Grid<99, 99, bool> visited{};

    const auto size = 99;
    int best = 0;

    auto score = [&]<int dx, int dy>(int x, int y) {
        auto height = input(x, y);

        auto s = 0;

        x += dx;
        y += dy;

        while (x < size && y < size & x >= 0 && y >= 0) {
            auto v = input(x, y);
            s++;
            if (v >= height) {
                break;
            }
            x += dx;
            y += dy;
        }

        return s;
    };

    auto ray = [&]<int dx, int dy>(int x, int y) {
        int height = -1;

        while (height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            int v = input(x, y);
            if (v > height) {
                height = v;
                if (visited(x, y) == 0) {
                    auto s = score.operator()<1, 0>(x, y) *
                             score.operator()<-1, 0>(x, y) *
                             score.operator()<0, 1>(x, y) *
                             score.operator()<0, -1>(x, y);

                    if (s > best) best = s;
                }
                visited(x, y) = true;
            }

            x += dx;
            y += dy;
        }
    };

    for (int i = 0; i < size; i++) {
        ray.operator()<1, 0>(0, i);
        ray.operator()<-1, 0>(98, i);
        ray.operator()<0, 1>(i, 0);
        ray.operator()<0, -1>(i, 98);
    }

    return best;
}

}  // namespace y2022::Day8
