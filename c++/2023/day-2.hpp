#pragma once

#include "../util.hpp"

namespace y2023::Day2 {

const auto input = readFile("../data/2023/day2.txt");

uint64_t part1() {
    uint64_t result = 0;

    bool ok = false;

    size_t pos = 1;
    size_t game = 0;
    while (pos < input.size()) {
        if (input[pos] == 'a') {
            result += ok * (game);
            game++;
            pos += 7 + (game > 9) + (game > 99);
            ok = true;
        } else {
            char v = input[pos++] - '0';
            while (input[pos] != ' ') {
                v = 10 * v + input[pos++] - '0';
            }
            pos += 2;
            auto col = (input[pos] >> 3) & 3;
            ok &= v <= 12 || (col == 2 && v <= 13) || (col == 1 && v <= 14);
            pos += 4 + col;
        }
    }
    result += ok * (game);

    return result;
}

uint64_t part2() {
    uint64_t result = 0;

    int r = 0, g = 0, b = 0;
    size_t pos = 1;
    size_t game = 0;
    while (pos < input.size()) {
        if (input[pos] == 'a') {
            result += r * g * b;
            r = g = b = 0;
            game++;
            pos += 7 + (game > 9) + (game > 99);
        } else {
            char v = input[pos++] - '0';
            while (input[pos] != ' ') {
                v = 10 * v + input[pos++] - '0';
            }
            pos += 2;
            int col = (input[pos] >> 3) & 3;

            if (col == 0)
                r = v > r ? v : r;
            else if (col == 2)
                g = v > g ? v : g;
            else
                b = v > b ? v : b;

            pos += 4 + col;
        }
    }
    result += r * g * b;

    return result;
}

}  // namespace y2023::Day2
