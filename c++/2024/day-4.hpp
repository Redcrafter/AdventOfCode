#pragma once
#include "../grid.hpp"
#include "../util.hpp"

namespace y2024::Day4 {

const auto input = readFile("../data/2024/day4.txt");

constexpr int h = 140;
constexpr int w = 140;

constexpr uint32_t xmas = 'XMAS';
constexpr uint32_t samx = 'SAMX';

auto parse() {
    Grid<w, h, uint8_t> g;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            g(x, y) = input[x + y * 141];
        }
    }
    return g;
}
auto grid = parse();

uint64_t part1() {
    uint64_t result = 0;
    for (int y = 0; y < h; y++) {
        uint32_t v1 = 0, v2 = 0;
        for (int x = 0; x < w; x++) {
            v1 = (v1 << 8) | grid(x, y);
            v2 = (v2 << 8) | grid(y, x);
            result += (v1 == xmas) + (v1 == samx) + (v2 == xmas) + (v2 == samx);
        }
    }
    for (int y = 0; y < h - 3; y++) {
        for (int x = 0; x < w - 3; x++) {
            const auto v1 = grid(x, y) | (grid(x + 1, y + 1) << 8) | (grid(x + 2, y + 2) << 16) | (grid(x + 3, y + 3) << 24);
            const auto v2 = grid(x + 3, y) | (grid(x + 2, y + 1) << 8) | (grid(x + 1, y + 2) << 16) | (grid(x, y + 3) << 24);
            result += (v1 == xmas) + (v1 == samx) + (v2 == xmas) + (v2 == samx);
        }
    }
    return result;
}

uint64_t part2() {
    uint64_t result = 0;
    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            const auto v = grid(x - 1, y - 1) | (grid(x + 1, y - 1) << 8) | (grid(x - 1, y + 1) << 16) | (grid(x + 1, y + 1) << 24);
            result += (grid(x, y) == 'A') * ((v == 'MMSS') + (v == 'MSMS') + (v == 'SSMM') + (v == 'SMSM'));
        }
    }
    return result;
}

}  // namespace y2024::Day4
