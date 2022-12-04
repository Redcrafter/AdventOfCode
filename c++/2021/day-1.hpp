#pragma once
#include <array>
#include <iostream>

#include "../util.hpp"

namespace Day1 {

std::array<uint16_t, 2000> parseData() {
    std::array<uint16_t, 2000> data;

    auto lines = readLines("../data/2021/day1.txt");

    for (size_t i = 0; i < lines.size(); i++) {
        data[i] = std::stoi(lines[i]);
    }

    return data;
}

const auto input = parseData();

uint64_t part1() {
    int count = 0;
    for (int i = 1; i < input.size(); i++) {
        count += input[i] > input[i - 1];
    }
    return count;
}

uint64_t part2() {
    int count = 0;
    for (int i = 3; i < input.size(); i++) {
        int last = input[i - 3] + input[i - 2] + input[i - 1];
        int current = input[i - 2] + input[i - 1] + input[i];
        count += current > last;
    }
    return count;
}

}  // namespace Day1
