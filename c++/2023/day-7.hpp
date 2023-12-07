#pragma once
#include <emmintrin.h>
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <iostream>

#include "../util.hpp"

namespace y2023::Day7 {

const auto input = readFile("../data/2023/day7.txt");

struct Card {
    uint32_t score;
    uint32_t bet;
};

uint32_t readInt(size_t& pos) {
    uint32_t val = 0;
    char c;
    while (isDigit(c = input[pos++])) {
        val = val * 10 + c - '0';
    }
    return val;
}

always__inline
auto parseCard(size_t& pos, std::array<int, 35>& scores, uint8_t charMap[]) {
    auto hand = *(uint64_t*)(input.data() + pos);
    pos += 6;
    auto bet = readInt(pos);

    scores.fill(0);
    int value = 0;
    for (size_t i = 0; i < 5; i++) {
        auto v = ((hand >> (i * 8)) & 0xFF) - '2';
        scores[v]++;
        value = (value << 4) | charMap[v];
    }

    auto five = false;
    auto four = false;
    auto three = false;
    auto two = 0;

    for (auto i : scores) {
        five |= i == 5;
        four |= i == 4;
        three |= i == 3;
        two += i == 2;
    }

    return std::tuple(five, four, three, two, value, bet);
}

always__inline
auto calcResult(std::array<Card, 1000>& cards) {
    std::sort(cards.begin(), cards.end(), [](auto a, auto b) { return a.score < b.score; });

    uint64_t result = 0;
    for (size_t i = 0; i < cards.size(); i++) {
        auto c = cards[i];
        result += (i + 1) * c.bet;
    }
    return result;
}

uint64_t part1() {
    std::array<Card, 1000> cards;
    uint8_t charMap[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 9, 11, 0, 0, 0, 0, 0, 10, 0, 0, 8};

    std::array<int, 35> scores;

    size_t pos = 0;
    for (size_t i = 0; i < 1000; i++) {
        auto [five, four, three, two, value, bet] = parseCard(pos, scores, charMap);

        uint32_t type = 0;

        if (five) type = 6;
        else if (four) type = 5;
        else if (three && two) type = 4;
        else if (three) type = 3;
        else if (two == 2) type = 2;
        else if (two == 1) type = 1;
        else type = 0;

        cards[i] = {(type * 16777216) | value, bet};
    }

    return calcResult(cards);
}

uint64_t part2() {
    std::array<Card, 1000> cards;
    uint8_t charMap[] = {1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 10, 0, 0, 9};

    std::array<int, 35> scores;

    size_t pos = 0;
    for (size_t i = 0; i < 1000; i++) {
        auto [five, four, three, two, value, bet] = parseCard(pos, scores, charMap);

        auto j = scores['J' - '2'];
        uint32_t type = 0;

        if (five) type = 6;
        else if (four) type = j ? 6 : 5;
        else if (three && two) type = j ? 6 : 4;
        else if (three) type = j ? 5 : 3;
        else if (two == 2) {
            if (j == 1) type = 4;
            else if (j == 2) type = 5;
            else type = 2;
        } else if (two == 1) type = j ? 3 : 1;
        else type = j ? 1 : 0;

        cards[i] = {(type * 16777216) | value, bet};
    }

    return calcResult(cards);
}

}  // namespace y2023::Day7
