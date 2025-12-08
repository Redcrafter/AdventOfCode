#pragma once
#include <algorithm>
#include <cmath>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2025::Day5 {

const auto input = aoc::getInput(2025, 5);

auto parse_nums(size_t& pos) {
    std::vector<std::pair<int64_t, int64_t>> nums;
    while(true) {
        auto a = readUInt<int64_t>(input, pos);
        auto b = readUInt<int64_t>(input, pos);
        nums.emplace_back(a, b);
        if(input[pos] == '\n') break;
    }
    pos++;

    std::sort(nums.begin(), nums.end(), [](auto& a, auto& b) { return a.first < b.first; });
    return nums;
}

uint64_t part1() {
    size_t pos = 0;
    auto nums = parse_nums(pos);

    std::vector<std::pair<int64_t, int64_t>> ranges;

    // combine and remove overlapping ranges
    int64_t end = 0;
    for(size_t i = 0; i < nums.size(); i++) {
        const auto [a, b] = nums[i];
        if(a - 1 <= end) { // overlaps with previous
            if(b > end) { // extend previous range
                ranges.back().second = b;
            }
            // else completely contained = ignore
        } else { // at least 1 gap
            ranges.emplace_back(a, b);
        }

        end = std::max(end, b);
    }

    uint64_t res = 0;
    while(pos < input.size()) {
        auto num = readUInt<int64_t>(input, pos);
        auto range = std::upper_bound(ranges.begin(), ranges.end(), num, [](const auto& a, const auto& b) { return a < b.second; });
        if(num >= range->first && num <= range->second) {
            res++;
        }
    }
    return res;
}

uint64_t part2() {
    size_t pos = 0;
    auto nums = parse_nums(pos);

    uint64_t res = 0;
    int64_t end = 0;
    for(auto [a, b] : nums) {
        if(a <= end) {
            a = end + 1;
        }
        end = std::max(end, b);

        if(a <= b) {
            res += b - a + 1;
        }
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 5, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 5, 2, "part2");

} // namespace y2025::Day5
