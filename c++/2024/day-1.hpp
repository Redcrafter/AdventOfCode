#pragma once
#include <array>
#include <cmath>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day1 {

const auto input = aoc::getInput(2024, 1);

template<size_t size>
void radixSortUint32(std::array<uint32_t, size>& input) {
    std::array<uint32_t, 256 * 4> count{0};
    std::array<uint32_t, size> output;

    // count all bytes in one pass
    for(int i = 0; i < input.size(); i++) {
        auto val = input[i];
        count[val & 0xFF]++;
        count[((val >> 8) & 0xFF) | 256]++;
        count[((val >> 16) & 0xFF) | 512]++;
        count[((val >> 24) & 0xFF) | 768]++;
    }

    // create summed array
    for(int j = 0; j < 4; j++) {
        auto t = 0;
        auto sum = 0;
        auto offset = j * 256;
        for(int i = 0; i < 256; i++) {
            t = count[i + offset];
            count[i + offset] = sum;
            sum += t;
        }
    }

    for(int i = 0; i < input.size(); i++) {
        auto val = input[i];
        output[count[val & 0xFF]++] = val;
    }
    for(int i = 0; i < input.size(); i++) {
        auto val = output[i];
        input[count[((val >> 8) & 0xFF) | 256]++] = val;
    }
    for(int i = 0; i < input.size(); i++) {
        auto val = input[i];
        output[count[((val >> 16) & 0xFF) | 512]++] = val;
    }
    for(int i = 0; i < input.size(); i++) {
        auto val = output[i];
        input[count[((val >> 24) & 0xFF) | 768]++] = val;
    }
}

auto parse() {
    std::array<uint32_t, 1000> l, r;

    for(size_t i = 0; i < 1000; i++) {
        l[i] = readExactInt<uint32_t, 5>(input.substr(i * 14));
        r[i] = readExactInt<uint32_t, 5>(input.substr(i * 14 + 8));
    }
    return std::pair(l, r);
}

uint64_t part1() {
    auto [l, r] = parse();

    radixSortUint32(l);
    radixSortUint32(r);

    uint64_t result = 0;
    for(int i = 0; i < l.size(); i++) {
        result += std::abs((int)l[i] - (int)r[i]);
    }
    return result;
}

uint64_t part2() {
    auto [l, r] = parse();

    std::array<uint8_t, 100000> map{};

    for(int i = 0; i < r.size(); i++) {
        map[r[i]]++;
    }

    uint64_t result = 0;
    for(int i = 0; i < l.size(); i++) {
        auto a = l[i];
        result += a * map[a];
    }
    return result;
}

static auto p1 = aoc::test(part1, 2024, 1, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 1, 2, "part2");

} // namespace y2024::Day1
