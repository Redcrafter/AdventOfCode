#pragma once
#include <array>
#include <vector>

#include "../grid.hpp"
#include "../util.hpp"

namespace y2023::Day17 {

const auto input = readFile("../data/2023/day17.txt");

const auto width = 141;
const auto height = 141;

struct El {
    vec2<int16_t> pos;
    bool vert;
};

using dt = Grid<width, height, uint8_t>;
using qt = std::array<std::vector<El>, 1024 + 512>;  // might not be big enough for some inputs?
using gt = Grid<width, height, std::array<uint16_t, 4>>;

template <int start, int end, int dx, int dy, bool vert>
always__inline void add(dt& dat, qt& queue, gt& grid, vec2<int16_t> pos, uint16_t dist) {
    vec2<int16_t> delta(dx, dy);
    pos += delta;

    for (size_t i = 1; i < start; i++) {
        if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
            return;

        dist += dat(pos);
        pos += delta;
    }

    for (size_t i = start; i <= end; i++) {
        if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
            return;

        dist += dat(pos);
        auto& g = grid(pos)[vert];
        if (dist < g) {
            g = dist;
            queue[dist].emplace_back(pos, vert);
        }
        pos += delta;
    }
}

template <bool part1>
uint64_t solve() {
    qt queue;
    for (size_t i = 0; i < queue.size(); i++) {
        queue[i].reserve(64);
    }

    dt dat;
    size_t pos = 0;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            dat(x, y) = input[pos++] & 0xF;
        }
        pos++;
    }

    gt grid;
    grid.fill({0xFFFF, 0xFFFF, 0, 0});

    const auto start = part1 ? 1 : 4;
    const auto end = part1 ? 3 : 10;

    add<start, end, 1, 0, false>(dat, queue, grid, {0, 0}, 0);
    add<start, end, 0, 1, true>(dat, queue, grid, {0, 0}, 0);

    for (size_t i = 0;; i++) {
        auto& q = queue[i];
        for (const auto& el : q) {
            if (el.pos.x == width - 1 && el.pos.y == height - 1) {
                return i;
            }

            auto& g = grid(el.pos)[el.vert + 2];
            if (g)
                continue;
            g = 1;

            if (el.vert) {
                add<start, end, -1, 0, false>(dat, queue, grid, el.pos, i);
                add<start, end, 1, 0, false>(dat, queue, grid, el.pos, i);
            } else {
                add<start, end, 0, -1, true>(dat, queue, grid, el.pos, i);
                add<start, end, 0, 1, true>(dat, queue, grid, el.pos, i);
            }
        }
    }
}

uint64_t part1() {
    return solve<true>();
}

uint64_t part2() {
    return solve<false>();
}

}  // namespace y2023::Day17
