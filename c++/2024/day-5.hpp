#pragma once
#include <array>
#include <vector>

#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2024::Day5 {

const auto input = readFile("../data/2024/day5.txt");

// longest is 23 entries
using listType = fixedVector<uint16_t, 24>;

auto parse() {
    std::array<uint8_t, 256 * 256> map{};
    std::vector<listType> vals;
    vals.reserve(1200);

    int i = 0;
    while (true) {
        if (input[i] == '\n') break;

        auto a = (input[i + 0] & 0xF) | ((input[i + 1] & 0xF) << 4);
        auto b = (input[i + 3] & 0xF) | ((input[i + 4] & 0xF) << 4);
        map[a | (b << 8)] = 1;

        i += 6;
    }
    i++;

    while (i < input.size()) {
        listType asd;
        while (true) {
            asd.push_back((input[i] & 0xF) | ((input[i + 1] & 0xF) << 4));
            i += 2;
            if (input[i++] == '\n')
                break;
        }
        vals.push_back(std::move(asd));
    }

    return std::pair(map, vals);
}

bool check(std::array<uint8_t, 256 * 256>& map, const listType& page) {
    for (int i = 1; i < page.size(); i++) {
        if (map[page[i] | (page[i - 1] << 8)]) {
            return false;
        }
    }
    return true;
}

uint64_t part1() {
    auto [map, vals] = parse();

    uint64_t result = 0;
    for (auto&& item : vals) {
        if (check(map, item)) {
            auto v = item[item.size() / 2];
            result += (v & 0xF) * 10 + (v >> 4);
        }
    }
    return result;
}

uint64_t part2() {
    auto [map, vals] = parse();

    uint64_t result = 0;
    for (auto&& item : vals) {
        auto eq = true;

        // insertion sort + equality check
        for (int i = 1; i < item.size(); i++) {
            auto a = item[i];
            auto j = i;
            for (; j > 0 && map[a | (item[j - 1] << 8)] == 1; j--) {
                item[j] = item[j - 1];
                eq = false;
            }
            item[j] = a;
        }
        if (!eq) {
            auto v = item[item.size() / 2];
            result += (v & 0xF) * 10 + (v >> 4);
        }
    }

    return result;
}

}  // namespace y2024::Day5
