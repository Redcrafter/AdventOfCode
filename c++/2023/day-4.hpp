#pragma once
#include <array>

#include "../util.hpp"

namespace y2023::Day4 {

const auto input = readFile("../data/2023/day4.txt");

always__inline
int countDup(size_t& pos, std::array<uint16_t, 10>& mine, std::array<uint16_t, 25>& winning) {
    pos += 10;

    for (int i = 0; i < 10; i++) {
        mine[i] = *(uint16_t*)(input.data() + pos);
        pos += 3;
    }
    pos += 2;

    for (int i = 0; i < 25; i++) {
        winning[i] = *(uint16_t*)(input.data() + pos);
        pos += 3;
    }
    pos++;
    int n = 0;
    for (int i = 0; i < 10; i++) {
        const auto item = mine[i];
        for (int j = 0; j < 25; j++) {
            n += item == winning[j];
        }
    }
    return n;
}

uint64_t part1() {
    uint64_t result = 0;

    std::array<uint16_t, 10> mine;
    std::array<uint16_t, 25> winning;

    size_t pos = 0;
    while (pos < input.length()) {
        int n = countDup(pos, mine, winning);
        result += (1 << n) >> 1;
    }

    return result;
}

uint64_t part2() {
    uint64_t result = 0;

    std::array<uint16_t, 10> mine;
    std::array<uint16_t, 25> winning;
    std::array<int, 200> copies;
    copies.fill(1);

    size_t pos = 0;
    int card = 0;
    while (pos < input.length()) {
        int n = countDup(pos, mine, winning);

        auto count = copies[card++];
        for (int j = 0; j < n; j++) {
            copies[card + j] += count;
        }
        result += count;
    }

    return result;
}

}  // namespace y2023::Day4
