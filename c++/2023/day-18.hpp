#pragma once

#include "../util.hpp"

namespace y2023::Day18 {

const auto input = readFile("../data/2023/day18.txt");

uint64_t part1() {
    size_t pos = 0;
    uint64_t m = 0;

    int y = 0;

    while (pos < input.size()) {
        auto dir = input[pos];
        pos += 2;

        auto dist = *(uint16_t*)(input.data() + pos);
        if ((dist >> 8) == ' ') {
            dist = dist & 0xF;
        } else {
            dist = ((dist >> 8) & 0xF) + (dist & 0xF) * 10;
            pos++;
        }
        pos += 12;

        if (dir == 'L') {
            m += 2 * y * dist + dist;
        } else if (dir == 'R') {
            m += -2 * y * dist + dist;
        } else if (dir == 'U') {
            y -= dist;
            m += dist;
        } else if (dir == 'D') {
            y += dist;
            m += dist;
        }
    }

    return m / 2 + 1;
}

uint64_t part2() {
    size_t pos = 0;
    uint64_t m = 0;

    int64_t y = 0;

    while (pos < input.size()) {
        pos += 6;
        auto dv = *(uint64_t*)(input.data() + pos);
        if((dv & 0xFF) == '#') {
            dv >>= 8;
            pos++;
        }
        pos += 8;
        auto dir = (dv >> 40) & 0xF;

        int dist = hextoint(dv);
        for (size_t i = 1; i < 5; i++) {
            dv >>= 8;
            dist = (dist << 4) | hextoint(dv);
        }

        if (dir == 2) {
            m += 2 * y * dist + dist;
        } else if (dir == 0) {
            m += -2 * y * dist + dist;
        } else if (dir == 3) {
            y -= dist;
            m += dist;
        } else if (dir == 1) {
            y += dist;
            m += dist;
        }
    }

    return m / 2 + 1;
}

}  // namespace y2023::Day18
