#pragma once
#include <array>

#include "../util.hpp"

namespace y2022::Day7 {

auto input = readLines("../data/2022/day7.txt");

int praseInt(const char* str) {
    int val = 0;
    for (int i = 0;; i++) {
        auto c = str[i];
        if (c == ' ') return val;

        val = val * 10 + c - 48;
    }
}

uint64_t part1() {
    auto res = 0;
    std::array<int, 32> stack;
    int sp = 0;

    for (auto i = 0; i < input.size();) {
        auto line = input[i];
        i++;

        if (line[2] == 'c') {
            if (line[5] == '/') {
            } else if (line[5] == '.') {
                if (stack[sp] < 100000)
                    res += stack[sp];
                stack[sp - 1] += stack[sp];
                sp--;
            } else {
                stack[++sp] = 0;
            }
        } else {
            while (i < input.size() && input[i][0] != '$') {
                if (input[i][0] != 'd') {
                    stack[sp] += praseInt(input[i].c_str());
                }
                i++;
            }
        }
    }

    return res;
}

uint64_t part2() {
    std::array<int, 1024> sizes;
    int pos = 0;

    std::array<int, 32> stack;
    int sp = 0;

    for (auto i = 0; i < input.size();) {
        auto line = input[i];
        i++;

        if (line[2] == 'c') {
            if (line[5] == '/') {
            } else if (line[5] == '.') {
                sizes[pos++] = stack[sp];
                stack[sp - 1] += stack[sp];
                sp--;
            } else {
                stack[++sp] = 0;
            }
        } else {
            while (i < input.size() && input[i][0] != '$') {
                if (input[i][0] != 'd') {
                    stack[sp] += praseInt(input[i].c_str());
                }
                i++;
            }
        }
    }

    int req = 30000000 - (70000000 - stack[0]);
    int m = 70000000;

    for (size_t i = 0; i < pos; i++) {
        auto v = sizes[i];
        if (v > req && v < m) m = sizes[i];
    }

    return m;
}

}  // namespace y2022::Day7
