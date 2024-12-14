#pragma once
#include <algorithm>
#include <array>
#include <tuple>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2023::Day5 {

const auto input = aoc::getInput(2023, 5);

always__inline auto parseInput() {
    std::vector<uint32_t> seeds;
    std::array<std::vector<std::tuple<uint32_t, uint32_t, uint32_t>>, 7> maps;

    size_t pos = 7;
    while(input[pos] != '\n') {
        seeds.push_back(readUInt(input, pos));
    }

    int n = 0;
    while(pos < input.size()) {
        auto& curr = maps[n++];
        curr.reserve(40);

        pos++;
        while(input[pos++] != '\n') {
        }

        while(pos < input.size() && input[pos] != '\n') {
            auto a = readUInt(input, pos);
            auto b = readUInt(input, pos);
            auto c = readUInt(input, pos);
            curr.emplace_back(a, b, c);
        }
    }

    return std::tuple(seeds, maps);
}

uint64_t part1() {
    const auto [seeds, maps] = parseInput();

    uint32_t result = -1;

    for(auto val : seeds) {
        for(const auto& map : maps) {
            for(const auto& [drs, srs, len] : map) {
                if(val >= srs && val < srs + len) {
                    val = (val - srs) + drs;
                    break;
                }
            }
        }
        result = std::min(val, result);
    }

    return result;
}

uint64_t part2() {
    auto [seeds, maps] = parseInput();

    for(auto& map : maps) {
        std::sort(map.begin(), map.end(), [](auto a, auto b) { return std::get<1>(a) < std::get<1>(b); });
        uint32_t max = std::get<1>(map[map.size() - 1]) + std::get<2>(map[map.size() - 1]);
        if(max != 0)
            map.emplace_back(max, max, -1);
    }

    std::vector<std::tuple<uint64_t, uint64_t>> ranges;
    std::vector<std::tuple<uint64_t, uint64_t>> n_ranges;
    ranges.reserve(32);
    n_ranges.reserve(32);

    for(int i = 0; i < seeds.size(); i += 2) {
        ranges.emplace_back(seeds[i], seeds[i] + seeds[i + 1]);
    }

    for(const auto& map : maps) {
        n_ranges.clear();
        for(const auto& [rs, re] : ranges) {
            auto test = std::lower_bound(map.begin(), map.end(), rs, [](const auto& a, const auto& b) { return std::get<1>(a) < b; });
            auto asd = std::distance(map.begin(), test);

            for(size_t i = asd - 1; i < map.size(); i++) {
                const auto [dest1, source1, sourcel] = map[i];
                if(re < source1)
                    break;

                auto start = std::max(rs, (uint64_t)source1);
                auto end = std::min(re, (uint64_t)source1 + (uint64_t)sourcel);
                if(start < end) // overlaps
                    n_ranges.emplace_back(start + dest1 - source1, end + dest1 - source1);
            }
        }
        std::swap(ranges, n_ranges);
    }

    uint64_t result = -1;
    for(auto [rs, re] : ranges) {
        result = std::min(result, rs);
    }
    return result;
}

static auto p1 = aoc::test(part1, 2023, 5, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 5, 2, "part2");

} // namespace y2023::Day5
