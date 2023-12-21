#pragma once
#include <array>
#include <unordered_map>
#include <vector>

#include "../util.hpp"

namespace y2023::Day21 {

const auto input = readFile("../data/2023/day21.txt");
const int size = 131;
const int start = (size - 1) / 2;

template <size_t s>
uint64_t count(const std::array<uint8_t, s>& arr) {
    uint64_t result = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == 1)
            result++;
    }
    return result;
}

auto getL(int x, int y) {
    x %= size;
    y %= size;
    return input[x + y * (size + 1)];
}

uint64_t calc(uint64_t a, uint64_t b, uint64_t c) {
    const uint64_t repeats = ((26501365 - 65) / 131);
    uint64_t delta = (c - b) - (b - a);
    return a + (b - a) * repeats + (delta * repeats * (repeats - 1)) / 2;
}

uint64_t part1() {
    Grid<size, size, uint8_t> a;
    Grid<size, size, uint8_t> b;

    auto* curr = &a;
    auto* next = &b;

    a.fill(0);
    a(start, start) = 1;

    for (size_t i = 0; i < 64; i++) {
        next->fill(0);

        auto s = start - i;
        auto e = start + i;

        for (size_t y = s; y <= e; y++) {
            for (size_t x = s; x <= e; x++) {
                if ((*curr)(x, y) == 0)
                    continue;

                if (input[(x - 1) + y * (size + 1)] != '#') (*next)(x - 1, y) = 1;
                if (input[(x + 1) + y * (size + 1)] != '#') (*next)(x + 1, y) = 1;
                if (input[x + (y - 1) * (size + 1)] != '#') (*next)(x, y - 1) = 1;
                if (input[x + (y + 1) * (size + 1)] != '#') (*next)(x, y + 1) = 1;
            }
        }

        std::swap(curr, next);
    }

    return count(curr->data);
}

uint64_t part2() {
    Grid<size * 5, size * 5, uint8_t> ga;
    Grid<size * 5, size * 5, uint8_t> gb;

    auto* curr = &ga;
    auto* next = &gb;

    ga.fill(0);
    ga(start + size * 2, start + size * 2) = 1;

    uint64_t a = 0;
    uint64_t b = 0;
    uint64_t c = 0;

    for (size_t i = 0; i < 65 + 131 * 2; i++) {
        next->fill(0);

        auto s = (start + size * 2) - i;
        auto e = (start + size * 2) + i;

        for (size_t y = s; y <= e; y++) {
            for (size_t x = s; x <= e; x++) {
                if ((*curr)(x, y) == 0)
                    continue;

                if (getL(x - 1, y) != '#') (*next)(x - 1, y) = 1;
                if (getL(x + 1, y) != '#') (*next)(x + 1, y) = 1;
                if (getL(x, y - 1) != '#') (*next)(x, y - 1) = 1;
                if (getL(x, y + 1) != '#') (*next)(x, y + 1) = 1;
            }
        }

        if (i == 65) {
            a = count(curr->data);
        }
        if (i == 65 + 131) {
            b = count(curr->data);
        }

        std::swap(curr, next);
    }
    c = count(curr->data);

    return calc(a, b, c);
}

// https://en.wikipedia.org/wiki/Flood_fill#Span_filling
void floodFill(Grid<size, size, uint8_t>& grid) {
    for (size_t y = 0; y < size; y++) {
        for (size_t x = 0; x < size; x++) {
            grid(x, y) = input[x + y * (size + 1)] == '#' ? 2 : 0;
        }
    }

    std::vector<std::tuple<int, int, int, int>> stack;

    {
        int x = 65;
        int y = 65;
        stack.emplace_back(x, x, y, 1);
        stack.emplace_back(x, x, y - 1, -1);
    }

    while (!stack.empty()) {
        auto el = stack.back();
        stack.pop_back();

        auto x1 = std::get<0>(el);
        auto x2 = std::get<1>(el);
        auto y = std::get<2>(el);
        auto dy = std::get<3>(el);

        auto x = x1;
        if (grid(x, y) == 0) {
            while (x > 0 && grid(x - 1, y) == 0) {
                grid(x - 1, y) = 1;
                x--;
            }
            if (x < x1 && y - dy >= 0 && y - dy < size) {
                stack.emplace_back(x, x1 - 1, y - dy, -dy);
            }
        }
        while (x1 <= x2) {
            while (x1 < size && grid(x1, y) == 0) {
                grid(x1, y) = 1;
                x1++;
            }
            if (x1 > x && y + dy >= 0 && y + dy < size)
                stack.emplace_back(x, x1 - 1, y + dy, dy);
            if (x1 - 1 > x2 && y - dy >= 0 && y - dy < size)
                stack.emplace_back(x2 + 1, x1 - 1, y - dy, -dy);
            x1++;
            while (x1 < x2 && grid(x1, y) != 0)
                x1++;
            x = x1;
        }
    }
}

uint64_t part1_cheat() {
    Grid<size, size, uint8_t> grid;
    floodFill(grid);

    uint64_t result = 0;
    for (int y = -start; y <= start; y++) {
        int range = start - std::abs(y);
        for (int x = -range; x <= range; x++) {
            if (grid(x + start, y + start) == 1 && !((x + y) & 1)) {
                result++;
            }
        }
    }
    return result;
}

uint64_t part2_cheat() {
    Grid<size, size, uint8_t> grid;
    floodFill(grid);

    uint64_t count64 = 0;
    uint64_t count65 = 0;

    for (int y = -start; y <= start; y++) {
        int range = start - std::abs(y);
        for (int x = -range; x <= range; x++) {
            if (grid(x + start, y + start) == 1) {
                count64 += !((x + y) & 1);
                count65 += (x + y) & 1;
            }
        }
    }

    uint64_t nCount64 = 0;
    uint64_t nCount65 = 0;

    for (int y = 0; y < size; y++) {
        int range = std::abs(start - y);
        for (int x = 0; x < range; x++) {
            if (grid(x, y) == 1) {
                nCount64 += (x + y) & 1;
                nCount65 += !((x + y) & 1);
            }
            auto x1 = size - x - 1;
            auto y1 = size - y - 1;
            if (grid(x1, y1) == 1) {
                nCount64 += (x1 + y1) & 1;
                nCount65 += !((x1 + y1) & 1);
            }
        }
    }

    auto a = count65;
    auto b = count64 * 1 + count65 * 4 + nCount64 * 2 + nCount65 * 2;
    auto c = count64 * 4 + count65 * 9 + nCount64 * 6 + nCount65 * 6;

    return calc(a, b, c);
}

}  // namespace y2023::Day21
