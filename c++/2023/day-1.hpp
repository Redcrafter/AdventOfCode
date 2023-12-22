#pragma once
#include "../util.hpp"

namespace y2023::Day1 {

const auto input = readFile("../data/2023/day1.txt");

uint64_t part1() {
    uint64_t count = 0;
    size_t pos = 0;
    while (pos < input.size()) {
        char last = 0;
        while (true) {
            auto c = input[pos++];
            if (isDigit(c)) {
                count += (c - '0') * 10;
                last = c;
                break;
            }
        }
        while (true) {
            auto c = input[pos++];
            if (c == '\n')
                break;
            if (isDigit(c))
                last = c;
        }
        count += last - '0';
    }

    return count;
}

constexpr uint64_t toNum(const std::string& str) {
    uint64_t val = 0;
    for (size_t i = 0; i < str.length(); i++) {
        val += ((uint64_t)str[i]) << (8 * i);
    }
    return val;
}

uint64_t part2() {
    uint64_t count = 0;
    size_t pos = 0;

    while (pos < input.length()) {
        while (true) {
            auto c = input[pos];
            auto test = *(uint64_t*)(input.data() + pos);
            pos++;

            if (isDigit(c)) {
                count += (c - '0') * 10;
                break;
            } else if ((test & 0xFFFFFF) == toNum("one")) {
                count += 10;
                break;
            } else if ((test & 0xFFFFFF) == toNum("two")) {
                count += 20;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("three")) {
                count += 30;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("four")) {
                count += 40;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("five")) {
                count += 50;
                break;
            } else if ((test & 0xFFFFFF) == toNum("six")) {
                count += 60;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("seven")) {
                count += 70;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("eight")) {
                count += 80;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("nine")) {
                count += 90;
                break;
            }
        }

        while (input[pos++] != '\n') {
        }

        for (int j = pos - 1;; j--) {
            auto c = input[j];
            auto test = *(uint64_t*)(input.data() + j);

            if (isDigit(c)) {
                count += (c - '0');
                break;
            } else if ((test & 0xFFFFFF) == toNum("one")) {
                count += 1;
                break;
            } else if ((test & 0xFFFFFF) == toNum("two")) {
                count += 2;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("three")) {
                count += 3;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("four")) {
                count += 4;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("five")) {
                count += 5;
                break;
            } else if ((test & 0xFFFFFF) == toNum("six")) {
                count += 6;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("seven")) {
                count += 7;
                break;
            } else if ((test & 0xFFFFFFFFFF) == toNum("eight")) {
                count += 8;
                break;
            } else if ((test & 0xFFFFFFFF) == toNum("nine")) {
                count += 9;
                break;
            }
        }
    }

    return count;
}

}  // namespace y2023::Day1
