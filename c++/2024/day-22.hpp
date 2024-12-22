#pragma once
#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2024::Day22 {

const auto input = extractNumbers<int>(aoc::getInput(2024, 22));

uint64_t part1() {
    uint64_t result = 0;
    for(int i = 0; i < input.size(); i++) {
        auto num = input[i];
        for(int j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = num ^ (num << 11);
        }
        result += num & 0xFFFFFF;
    }
    return result;
}

uint64_t part2() {
    std::array<uint16_t, 1 << 20> possible{};
    std::array<bool, 1 << 20> sub{};
    fixedVector<uint32_t, 2000> is; // keeping track of set indecies is slightly faster than std::bitset

    for(int i = 0; i < input.size(); i++) {
        int num = input[i];
        uint32_t last = num % 10;

        int seq = 0;
        for(int j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = (num ^ (num << 11)) & 0xFFFFFF;

            auto d = num % 10;
            seq = ((seq << 5) + ((d - last) + 9)) & 0xFFFFF;
            last = d;

            if(j >= 3 && !sub[seq]) {
                is.push_back(seq);
                sub[seq] = true;
                possible[seq] += d;
            }
        }

        for(auto i : is)
            sub[i] = 0;
        is.clear();
    }

    return std::ranges::max(possible);
}

static auto p = aoc::test([]() { return extractNumbers<int>(aoc::getInput(2024, 22)).size(); }, 2024, 22, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 22, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 22, 2, "part 2");

} // namespace y2024::Day22
