#pragma once
#include <vector>

#include "../util.hpp"

namespace y2024::Day3 {

const auto input = readFile("../data/2024/day3.txt");

uint64_t part1() {
    uint64_t result = 0;

    size_t pos = 0;
    while (pos < input.size()) {
        if (stringMatch<"mul(">(input, pos)) {
            auto a = readUInt(input, pos);
            pos--;
            if (input[pos] != ',') {
                continue;
            }
            pos++;
            auto b = readUInt(input, pos);
            pos--;
            if (input[pos] != ')') {
                continue;
            }
            result += a * b;
        }
        pos++;
    }

    return result;
}

uint64_t part2() {
    uint64_t result = 0;

    bool en = true;
    size_t pos = 0;
    while (pos < input.size()) {
        if (stringMatch<"don't()">(input, pos)) {
            en = false;
            continue;
        }
        if (stringMatch<"do()">(input, pos)) {
            en = true;
            continue;
        }
        if (en && stringMatch<"mul(">(input, pos)) {
            auto a = readUInt(input, pos);
            pos--;
            if (input[pos] != ',') {
                continue;
            }
            pos++;
            auto b = readUInt(input, pos);
            pos--;
            if (input[pos] != ')') {
                continue;
            }
            result += a * b;
        }
        pos++;
    }

    return result;
}

}  // namespace y2024::Day3
