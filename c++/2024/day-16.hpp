#pragma once
#include <algorithm>
#include <iostream>
#include <queue>

#include "../aoc.hpp"
#include "../grid.hpp"

namespace y2024::Day16 {

const auto input = aoc::getInput(2024, 16);

const int width = 141;
const int height = 141;
const int width1 = width + 1;

struct El {
    vec2<uint8_t> pos;
    vec2<int8_t> dir;
    uint32_t score;

    friend bool operator<(const El& left, const El& right) {
        return left.score < right.score;
    }
};

auto calcGrid() {
    Grid<width, height, uint32_t> grid;
    grid.fill(1 << 30);

    std::vector<El> stack;
    stack.reserve(5000);
    stack.push_back({{1, height - 2}, {1, 0}, 0});
    stack.push_back({{1, height - 2}, {0, -1}, 1000});

    for(int i = 0; i < stack.size(); i++) {
        auto [pos, d, score] = stack[i];

        auto p1 = vec2<int>(pos) + vec2<int>(d);
        score++;

        if(score < grid(p1)) {
            grid(p1) = score;
        } else {
            continue;
        }

        while(true) {
            if(input[p1.x + p1.y * width1] == '#') break;

            if(input[(p1.x - d.y) + (p1.y + d.x) * width1] != '#') {
                stack.push_back({vec2<uint8_t>(p1), vec2<int8_t>(-d.y, d.x), score + 1000});
            }
            if(input[(p1.x + d.y) + (p1.y - d.x) * width1] != '#') {
                stack.push_back({vec2<uint8_t>(p1), vec2<int8_t>(d.y, -d.x), score + 1000});
            }

            if(score < grid(p1)) {
                grid(p1) = score;
            }

            score++;
            p1 += vec2<int>(d);
        }
    }
    return grid;
}

uint64_t part1() {
    auto grid = calcGrid();
    return grid(width - 2, 1);
}

bool trace(vec2<int> pos, vec2<int> dir, uint32_t score, Grid<width, height, uint32_t>& grid, Grid<width, height, bool>& visited) {
    auto last = pos;

    pos += dir;
    score--;

    if(grid(pos) != score) return false;
    if(visited(pos)) return true;
    visited(pos) = true;

    bool valid = false;
    while(true) {
        if(input[pos.x + pos.y * width1] == '#') break;

        visited(pos) = true;
        if(pos == vec2<int>(1, height - 2)) {
            return true;
        }

        if(input[(pos.x - dir.y) + (pos.y + dir.x) * width1] != '#') {
            if(trace(pos, {-dir.y, dir.x}, score - 1000, grid, visited)) {
                valid = true;
                last = pos;
            }
        }
        if(input[(pos.x + dir.y) + (pos.y - dir.x) * width1] != '#') {
            if(trace(pos, {dir.y, -dir.x}, score - 1000, grid, visited)) {
                valid = true;
                last = pos;
            }
        }

        pos += dir;
        score--;
    }

    pos -= dir;
    while(pos != last) { // go back to last valid location and clean up unused spaces
        visited(pos) = false;
        pos -= dir;
    }

    return valid;
}

uint64_t part2() {
    auto grid = calcGrid();

    Grid<width, height, bool> visited{};
    visited(width - 2, 1) = true;
    trace({width - 2, 1}, {-1, 0}, grid(width - 2, 1), grid, visited);
    trace({width - 2, 1}, {0, 1}, grid(width - 2, 1), grid, visited);

    uint64_t result = 0;
    for(size_t i = 0; i < visited.data.size(); i++) {
        result += visited.data[i];
    }
    return result;
}

static auto p1 = aoc::test(part1, 2024, 16, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 16, 2, "part 2");

} // namespace y2024::Day16
