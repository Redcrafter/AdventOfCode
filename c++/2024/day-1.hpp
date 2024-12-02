#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <unordered_map>
#include <vector>

#include "../util.hpp"

namespace y2024::Day1 {

const auto input = readFile("../data/2024/day1.txt");

void radixSortUint32(std::vector<uint32_t>& input) {
    std::array<uint32_t, 256 * 4> count {0};
    std::vector<uint32_t> output(input.size());

    // count all bytes in one pass
    for (int i = 0; i < input.size(); i++) {
        auto val = input[i];
        count[val & 0xFF]++;
        count[((val >> 8) & 0xFF) | 256]++;
        count[((val >> 16) & 0xFF) | 512]++;
        count[((val >> 24) & 0xFF) | 768]++;
    }

    // create summed array
    for (int j = 0; j < 4; j++) {
        auto t = 0;
        auto sum = 0;
        auto offset = j * 256;
        for (int i = 0; i < 256; i++) {
            t = count[i + offset];
            count[i + offset] = sum;
            sum += t;
        }
    }

    for (int i = 0; i < input.size(); i++) {
        auto val = input[i];
        output[count[val & 0xFF]++] = val;
    }
    for (int i = 0; i < input.size(); i++) {
        auto val = output[i];
        input[count[((val >> 8) & 0xFF) | 256]++] = val;
    }
    for (int i = 0; i < input.size(); i++) {
        auto val = input[i];
        output[count[((val >> 16) & 0xFF) | 512]++] = val;
    }
    for (int i = 0; i < input.size(); i++) {
        auto val = output[i];
        input[count[((val >> 24) & 0xFF) | 768]++] = val;
    }
}

auto parse() {
    std::vector<uint32_t> l(1000), r(1000);
    for (size_t i = 0; i < input.size();) {
        l.push_back(readUInt(input, i));
        i += 2;
        r.push_back(readUInt(input, i));
    }
    return std::pair(l, r);
}

uint64_t part1() {
    auto [l, r] = parse();

    radixSortUint32(l);
    radixSortUint32(r);

    uint64_t result = 0;
    for (size_t i = 0; i < l.size(); i++) {
        result += std::abs((int)l[i] - (int)r[i]);
    }
    return result;
}

uint64_t part2() {
    auto [l, r] = parse();

    std::array<uint16_t, 100000> map {0};

    for (size_t i = 0; i < r.size(); i++) {
        map[r[i]]++;
    }

    uint64_t result = 0;
    for (size_t i = 0; i < l.size(); i++) {
        auto a = l[i];
        result += a * map[a];
    }
    return result;
}

}  // namespace y2024::Day1
