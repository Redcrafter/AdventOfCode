#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>

namespace y2021::Day7 {

std::array<int, 1000> parseData() {
    std::array<int, 1000> data;

    auto line = readLines("../data/2021/day7.txt");
    auto lines = split(line[0], ',');

    for (size_t i = 0; i < lines.size(); i++) {
        data[i] = std::stoi(lines[i]);
    }

    return data;
}

const auto input = parseData();

template <int part>
uint64_t func() {
    static_assert(part == 1 || part == 2, "invalid day");

    int min = std::numeric_limits<int>::max();
    int max = 0;

    for (auto item : input) {
        min = std::min(min, item);
        max = std::max(max, item);
    }

    unsigned int best = -1;
    for (int i = min; i < max; i++) {
        int cost = 0;
        for (int j = 0; j < input.size(); j++) {
            auto val = std::abs(input[j] - i);
            if (part == 1) {
                cost += val;
            } else if (part == 2) {
                cost += (val * (val + 1)) / 2;
            }
        }

        if (cost < best)
            best = cost;
        else
            break;
    }
    return best;
}

}  // namespace y2021::Day7
