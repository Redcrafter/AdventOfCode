#pragma once
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day3 {

const auto input = aoc::getInput(2024, 3);

uint64_t part1() {
    uint64_t result = 0;

    size_t pos = 0;
    while(pos < input.size()) {
        if(stringMatch<"mul(">(input, pos)) {
            auto a = readUInt(input, pos);
            pos--;
            if(input[pos] != ',') {
                continue;
            }
            pos++;
            auto b = readUInt(input, pos);
            pos--;
            if(input[pos] != ')') {
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
    while(pos < input.size()) {
        if(stringMatch<"don't()">(input, pos)) {
            en = false;
            continue;
        }
        if(stringMatch<"do()">(input, pos)) {
            en = true;
            continue;
        }
        if(en && stringMatch<"mul(">(input, pos)) {
            auto a = readUInt(input, pos);
            pos--;
            if(input[pos] != ',') {
                continue;
            }
            pos++;
            auto b = readUInt(input, pos);
            pos--;
            if(input[pos] != ')') {
                continue;
            }
            result += a * b;
        }
        pos++;
    }

    return result;
}

static auto p1 = aoc::test(part1, 2024, 3, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 3, 2, "part2");

} // namespace y2024::Day3
