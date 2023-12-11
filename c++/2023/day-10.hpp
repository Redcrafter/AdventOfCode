#pragma once
#include <emmintrin.h>
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <vector>

#include "../util.hpp"

namespace y2023::Day10 {

const auto input = readFile("../data/2023/day10.txt");
const auto width = 141;

enum Dir {
    Top = 0,
    Bottom = 1 << 6,
    Left = 2 << 6,
    Right = 3 << 6
};

struct Position {
    int pos;
    Dir from;
};

always__inline auto getStarts(int start) {
    std::array<Position, 2> starts;
    int i = 0;
    {
        auto t = input[start - width];
        if (t == '|' || t == '7' || t == 'F')
            starts[i++] = {start - width, Dir::Bottom};

        auto b = input[start + width];
        if (b == '|' || b == 'L' || b == 'J')
            starts[i++] = {start + width, Dir::Top};

        auto l = input[start - 1];
        if (l == '-' || l == 'L' || l == 'F')
            starts[i++] = {start - 1, Dir::Right};

        auto r = input[start + 1];
        if (r == '-' || r == 'J' || r == '7')
            starts[i++] = {start + 1, Dir::Left};
    }
    return starts;
}

always__inline void step(Position& p) {
    switch ((input[p.pos] & 0x1F) | p.from) {
        case ('|' & 0x1F) | Dir::Top:
        case ('7' & 0x1F) | Dir::Left:
        case ('F' & 0x1F) | Dir::Right:
            p.pos += width;
            p.from = Dir::Top;
            break;
        case ('|' & 0x1F) | Dir::Bottom:
        case ('J' & 0x1F) | Dir::Left:
        case ('L' & 0x1F) | Dir::Right:
            p.pos -= width;
            p.from = Dir::Bottom;
            break;
        case ('-' & 0x1F) | Dir::Left:
        case ('L' & 0x1F) | Dir::Top:
        case ('F' & 0x1F) | Dir::Bottom:
            p.pos++;
            p.from = Dir::Left;
            break;
        case ('-' & 0x1F) | Dir::Right:
        case ('J' & 0x1F) | Dir::Top:
        case ('7' & 0x1F) | Dir::Bottom:
            p.pos--;
            p.from = Dir::Right;
            break;
    }
}

uint64_t part1() {
    int start = findChar(input.data(), 'S');
    auto starts = getStarts(start);

    int i = 2;
    while (true) {
        if (starts[0].pos == starts[1].pos) {
            break;
        }
        step(starts[0]);
        i++;

        if (starts[0].pos == starts[1].pos) {
            break;
        }
        step(starts[1]);
        i++;
    }
    return (i + 1) / 2;
}

uint64_t part2() {
    int start = findChar(input.data(), 'S');
    auto starts = getStarts(start);

    auto lx = start % width;
    auto ly = start / width;

    auto pos = starts[0].pos;
    auto from = starts[0].from;
    auto x = pos % width;
    auto y = pos / width;

    auto area = 0;
    auto count = 0;

    while (true) {
        area += (ly + y) * (lx - x);
        lx = x;
        ly = y;
        count++;

        if (pos == start)
            break;

        // have to copy this code because of x and y
        switch ((input[pos] & 0x1F) | from) {
            case ('|' & 0x1F) | Dir::Top:
            case ('7' & 0x1F) | Dir::Left:
            case ('F' & 0x1F) | Dir::Right:
                pos += width;
                y++;
                from = Dir::Top;
                break;
            case ('|' & 0x1F) | Dir::Bottom:
            case ('J' & 0x1F) | Dir::Left:
            case ('L' & 0x1F) | Dir::Right:
                pos -= width;
                y--;
                from = Dir::Bottom;
                break;
            case ('-' & 0x1F) | Dir::Left:
            case ('L' & 0x1F) | Dir::Top:
            case ('F' & 0x1F) | Dir::Bottom:
                pos++;
                x++;
                from = Dir::Left;
                break;
            case ('-' & 0x1F) | Dir::Right:
            case ('J' & 0x1F) | Dir::Top:
            case ('7' & 0x1F) | Dir::Bottom:
                pos--;
                x--;
                from = Dir::Right;
                break;
        }
    }

    // https://en.wikipedia.org/wiki/Shoelace_formula
    // https://en.wikipedia.org/wiki/Pick's_theorem
    return std::abs(area / 2) - (count / 2) + 1;
}

}  // namespace y2023::Day10
