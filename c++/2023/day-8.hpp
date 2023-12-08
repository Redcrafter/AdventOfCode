#pragma once
#include <array>

#include "../util.hpp"

namespace y2023::Day8 {

const auto input = readFile("../data/2023/day8.txt");

std::array<std::array<uint32_t, 2>, 'ZZZ' + 1> map; // too big for heap. causes segfault

uint64_t part1() {
    size_t pos = 0;
    while (input[pos++] != '\n') {
    }
    auto dirLen = pos - 1;
    pos++;

    while (pos < input.size()) {
        auto id = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 7;
        auto l = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 5;
        auto r = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 5;

        map[id] = {l, r};
    }

    auto curr = 'AAA';
    int i = 0;
    while (curr != 'ZZZ') {
        curr = map[curr][input[(i++) % dirLen] == 'L' ? 0 : 1];
    }
    return i;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
    }
    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return a * (b / gcd(a, b));
}

uint64_t part2() {
    size_t pos = 0;
    while (input[pos++] != '\n') {
    }
    auto dirLen = pos - 1;
    pos++;

    std::vector<int> starts;

    while (pos < input.size()) {
        auto id = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 7;
        auto l = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 5;
        auto r = (*(uint32_t*)(input.data() + pos)) & 0xFFFFFF;
        pos += 5;

        map[id] = {l, r};
        if ((id >> 16) == 'A') {
            starts.push_back(id);
        }
    }

    uint64_t result = 1;
    for (size_t i = 0; i < starts.size(); i++) {
        auto curr = starts[i];
        int j = 0;
        while ((curr >> 16) != 'Z') {
            curr = map[curr][input[(j++) % dirLen] == 'L' ? 0 : 1];
        }
        result = lcm(j, result);
    }

    return result;
}

}  // namespace y2023::Day8
