#pragma once
#include <array>
#include <span>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2023::Day12 {

const auto input = aoc::getInput(2023, 12);

std::array<int64_t, 128 * 32> cache;

uint64_t rec(std::span<const char> line, std::span<const uint32_t> nums, uint32_t numi, uint32_t pos) {
    auto id = (numi * 128) + pos;
    if(cache[id] != -1)
        return cache[id];

    const auto num = nums[numi];

    auto end = pos + num;

    if(end > line.size() || (end < line.size() && line[end] == '#') || contains(line.subspan(pos, num), '.')) {
        cache[id] = 0;
        return 0;
    }
    if(numi + 1 < nums.size()) {
        uint64_t n = 0;
        for(int i = end + 1; i < line.size(); i++) {
            n += rec(line, nums, numi + 1, i);
            if(line[i] == '#') {
                break;
            }
        }
        cache[id] = n;
        return n;
    }
    if(contains(line.data(), end + 1, line.size(), '#')) {
        cache[id] = 0;
        return 0;
    }

    cache[id] = 1;
    return 1;
}

uint64_t solveLine(std::span<const char> line, std::span<const uint32_t> nums) {
    uint64_t asd = 0;
    cache.fill(-1);
    for(int i = 0; i < line.size(); i++) {
        asd += rec(line, nums, 0, i);
        if(line[i] == '#') {
            break;
        }
    }
    return asd;
}

uint64_t part1() {
    std::vector<uint32_t> nums;

    uint64_t result = 0;

    size_t pos = 0;
    while(pos < input.size()) {
        auto s = pos;
        while(input[pos++] != ' ') {
        }

        auto line = std::span<const char>(input.data() + s, pos - s - 1);

        nums.clear();
        while(true) {
            auto n = readUInt(input, pos);
            nums.push_back(n);

            if(input[pos - 1] == '\n') {
                break;
            }
        }

        result += solveLine(line, nums);
    }

    return result;
}

uint64_t part2() {
    std::vector<char> line;
    std::vector<uint32_t> nums;

    uint64_t result = 0;

    size_t pos = 0;
    while(pos < input.size()) {
        line.clear();
        while(true) {
            char c = input[pos++];
            if(c == ' ') break;
            line.push_back(c);
        }

        nums.clear();
        while(true) {
            auto n = readUInt(input, pos);
            nums.push_back(n);

            if(input[pos - 1] == '\n') {
                break;
            }
        }

        auto ls = line.size();
        auto ns = nums.size();

        for(size_t i = 0; i < 4; i++) {
            line.push_back('?');
            for(size_t j = 0; j < ls; j++) {
                line.push_back(line[j]);
            }
            for(size_t j = 0; j < ns; j++) {
                nums.push_back(nums[j]);
            }
        }

        result += solveLine(line, nums);
    }
    return result;
}

static auto p1 = aoc::test(part1, 2023, 12, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 12, 2, "part2");

} // namespace y2023::Day12
