#pragma once
#include "../aoc.hpp"
#include "../grid.hpp"

namespace y2022::Day8 {

auto input = aoc::getInput(2022, 8);

uint64_t part1() {
    Grid<99, 99, bool> visited{};

    const auto size = 99;
    int count = 0;

    auto ray = [&]<int dx, int dy>(int x, int y) {
        int height = -1;

        while(height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            int v = input[x + y * 100] - '0';
            if(v > height) {
                height = v;
                count += visited(x, y) == 0;
                visited(x, y) = true;
            }

            x += dx;
            y += dy;
        }
    };

    for(int i = 0; i < size; i++) {
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
        auto height = input[x + y * 100] - '0';

        auto s = 0;

        x += dx;
        y += dy;

        while(x < size && y < size & x >= 0 && y >= 0) {
            auto v = input[x + y * 100] - '0';
            s++;
            if(v >= height) {
                break;
            }
            x += dx;
            y += dy;
        }

        return s;
    };

    auto ray = [&]<int dx, int dy>(int x, int y) {
        int height = -1;

        while(height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            int v = input[x + y * 100] - '0';
            if(v > height) {
                height = v;
                if(visited(x, y) == 0) {
                    auto s = score.operator()<1, 0>(x, y) *
                             score.operator()<-1, 0>(x, y) *
                             score.operator()<0, 1>(x, y) *
                             score.operator()<0, -1>(x, y);

                    if(s > best) best = s;
                }
                visited(x, y) = true;
            }

            x += dx;
            y += dy;
        }
    };

    for(int i = 0; i < size; i++) {
        ray.operator()<1, 0>(0, i);
        ray.operator()<-1, 0>(98, i);
        ray.operator()<0, 1>(i, 0);
        ray.operator()<0, -1>(i, 98);
    }

    return best;
}

static auto p1 = aoc::test(part1, 2022, 8, 1, "part1");
static auto p2 = aoc::test(part2, 2022, 8, 2, "part2");

} // namespace y2022::Day8
