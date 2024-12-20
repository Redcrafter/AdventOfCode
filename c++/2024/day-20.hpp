#pragma once
#include "../aoc.hpp"
#include "../grid.hpp"

namespace y2024::Day20 {

const auto input = aoc::getInput(2024, 20);
const int width = 141;
const int height = 141;
const int width1 = width + 1;

auto makeGrid() {
    Grid<width, height, int> grid;
    grid.fill(0xFFFF);

    vec2<int> start, end;

    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            if(input[x + y * width1] == 'S')
                start = {x, y};
            if(input[x + y * width1] == 'E')
                end = {x, y};
        }
    }

    auto pos = end;
    vec2<int> delta{1, 0};
    int i = 0;
    grid(pos) = i++;

    while(true) {
        while(true) {
            pos += delta;
            if(input[pos.x + pos.y * width1] == '#') break;
            grid(pos) = i++;
        }
        pos -= delta;

        if(pos == start) break;

        if(input[pos.x + delta.y + (pos.y - delta.x) * width1] != '#') {
            std::tie(delta.x, delta.y) = std::pair(delta.y, -delta.x);
        }
        if(input[pos.x - delta.y + (pos.y + delta.x) * width1] != '#') {
            std::tie(delta.x, delta.y) = std::pair(-delta.y, delta.x);
        }
    }
    return grid;
}

uint64_t solve(int r) {
    auto grid = makeGrid();

    uint64_t count = 0;
    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            auto sv = grid(x, y);
            if(sv == 0xFFFF) continue;

            for(int y1 = std::max(0, y - r); y1 <= std::min(y + r, height - 1); y1++) {
                auto yd = std::abs(y1 - y);
                auto r2 = r - yd;

                for(int x1 = std::max(0, x - r2); x1 <= std::min(x + r2, width - 1); x1++) {
                    auto ev = grid(x1, y1);
                    if(ev + 99 + std::abs(x - x1) + yd < sv) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

uint64_t part1_fast() {
    auto grid = makeGrid();

    uint64_t count = 0;
    for(int y = 1; y < height - 1; y++) {
        for(int x = 1; x < width - 1; x++) {
            auto sv = grid(x, y);
            if(sv == 0xFFFF) continue;

            if(x >= 2 && grid(x - 2, y) + 100 < sv) count++;
            if(x + 2 < width && grid(x + 2, y) + 100 < sv) count++;
            if(y >= 2 && grid(x, y - 2) + 100 < sv) count++;
            if(y + 2 < height && grid(x, y + 2) + 100 < sv) count++;
        }
    }
    return count;
}

uint64_t part1() {
    return solve(2);
}

uint64_t part2() {
    return solve(20);
}

static auto p1 = aoc::test(part1, 2024, 20, 1, "part 1");
static auto p1f = aoc::test(part1_fast, 2024, 20, 1, "part 1 fast");
static auto p2 = aoc::test(part2, 2024, 20, 2, "part 2");

} // namespace y2024::Day20
