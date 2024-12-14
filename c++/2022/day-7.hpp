#pragma once
#include <array>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2022::Day7 {

auto input = split(aoc::getInput(2022, 7), '\n');

int praseInt(std::string_view str) {
    int val = 0;
    for(int i = 0; i < str.size(); i++) {
        auto c = str[i];
        if(c == ' ') break;

        val = val * 10 + c - 48;
    }
    return val;
}

uint64_t part1() {
    auto res = 0;
    std::array<int, 32> stack{};
    int sp = 0;

    for(auto i = 0; i < input.size();) {
        auto& line = input[i];
        i++;

        if(line[2] == 'c') {
            if(line[5] == '/') {
            } else if(line[5] == '.') {
                if(stack[sp] < 100000)
                    res += stack[sp];
                stack[sp - 1] += stack[sp];
                sp--;
            } else {
                stack[++sp] = 0;
            }
        } else {
            while(i < input.size() && input[i][0] != '$') {
                if(input[i][0] != 'd') {
                    stack[sp] += praseInt(input[i]);
                }
                i++;
            }
        }
    }

    return res;
}

uint64_t part2() {
    std::array<int, 1024> sizes{};
    int pos = 0;

    std::array<int, 32> stack{};
    int sp = 0;

    for(auto i = 0; i < input.size();) {
        auto& line = input[i];
        i++;

        if(line[2] == 'c') {
            if(line[5] == '/') {
            } else if(line[5] == '.') {
                sizes[pos++] = stack[sp];
                stack[sp - 1] += stack[sp];
                sp--;
            } else {
                stack[++sp] = 0;
            }
        } else {
            while(i < input.size() && input[i][0] != '$') {
                if(input[i][0] != 'd') {
                    stack[sp] += praseInt(input[i]);
                }
                i++;
            }
        }
    }

    int req = 30000000 - (70000000 - stack[0]);
    int m = 70000000;

    for(size_t i = 0; i < pos; i++) {
        auto v = sizes[i];
        if(v > req && v < m) m = sizes[i];
    }

    return m;
}

static auto p1 = aoc::test(part1, 2022, 7, 1, "part1");
static auto p2 = aoc::test(part2, 2022, 7, 2, "part2");

} // namespace y2022::Day7
