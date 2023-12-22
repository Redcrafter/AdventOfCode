#pragma once
#include <array>
#include <vector>

#include "../util.hpp"

namespace y2023::Day8 {

const auto input = readFile("../data/2023/day8.txt");

const auto ZZZ = 'Z' + ('Z' << 8) + ('Z' << 16);
const auto AAA = 'A' + ('A' << 8) + ('A' << 16);

std::array<std::array<uint32_t, 2>, ZZZ + 1> map;  // too big for stack. causes segfault

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

    auto curr = AAA;
    int i = 0;
    while (curr != ZZZ) {
#pragma clang loop unroll_count(8)
        for (int j = 0; j < dirLen; j++)
            curr = map[curr][input[j] == 'L' ? 0 : 1];
        i += dirLen;
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
#pragma clang loop unroll_count(8)
            for (int k = 0; k < dirLen; k++)
                curr = map[curr][input[k] == 'L' ? 0 : 1];
            j += dirLen;
        }
        result = lcm(j, result);
    }

    return result;
}

uint64_t part1_cheat() {
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

    auto curr = AAA;
    int i = 0;
    while (curr != ZZZ) {
        curr = map[curr][1];
        i += dirLen;
    }
    return i;
}

uint64_t part2_cheat() {
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
            curr = map[curr][1];
            j += dirLen;
        }
        result = lcm(j, result);
    }

    return result;
}

}  // namespace y2023::Day8
