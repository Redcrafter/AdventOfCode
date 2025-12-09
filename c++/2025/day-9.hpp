#pragma once
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2025::Day9 {

const auto input = aoc::getInput(2025, 9);

auto parse() {
    std::vector<std::pair<int, int>> nums;
    size_t pos = 0;
    while(pos < input.length()) {
        auto a = readUInt(input, pos);
        auto b = readUInt(input, pos);
        nums.emplace_back(a, b);
    }
    return nums;
}

const auto parsed = parse();

template<typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

uint64_t part1() {
    int64_t max = 0;
    for(size_t i = 0; i < parsed.size(); i++) {
        auto [x1, y1] = parsed[i];
        for(size_t j = 0; j < i; j++) {
            auto [x2, y2] = parsed[j];

            max = std::max(max, (int64_t)(std::abs(x1 - x2) + 1) * (std::abs(y1 - y2) + 1));
        }
    }
    return max;
}

void test(int i, int end, int64_t& max) {
    auto [x1, y1] = parsed[i];

    for(size_t j = 0; j < end; j++) {
        auto [x2, y2] = parsed[j];

        auto dx = std::abs(x2 - x1) + 1;
        auto dy = std::abs(y2 - y1) + 1;
        auto area = (int64_t)dx * dy;
        if(area <= max) continue;

        auto l = std::min(x1, x2);
        auto r = std::max(x1, x2);
        auto b = std::min(y1, y2);
        auto t = std::max(y1, y2);

        auto valid = true;
        for(auto [x3, y3] : parsed) {
            if((l < x3 && x3 < r) && (b < y3 && y3 < t)) {
                valid = false;
                break;
            }
        }
        if(!valid) continue;

        auto [_x1, _y1] = parsed[parsed.size() - 1];
        for(int k = 0; k < parsed.size(); k++) {
            auto [_x2, _y2] = parsed[k];

            if(_x1 == _x2) {
                if((l < _x1 && _x1 < r) && ((_y1 <= t && _y2 >= b) || (_y2 <= t && _y1 >= b))) {
                    valid = false;
                    break;
                }
            } else {
                if((b < _y1 && _y1 < t) && ((_x1 <= l && _x2 >= r) || (_x2 <= l && _x1 >= r))) {
                    valid = false;
                    break;
                }
            }
            _x1 = _x2;
            _y1 = _y2;
        }

        if(!valid) continue;
        max = std::max(max, area);
    }
}

uint64_t part2() {
    int64_t max = 0;
    for(size_t i = 0; i < parsed.size(); i++) {
        test(i, i, max);
    }
    return max;
}

uint64_t part2_shortcut() {
    std::pair<int, int> e1{0, 0}, e2{0, 0};

    { // find longest edges
        auto [x1, y1] = parsed[parsed.size() - 1];
        for(int k = 0; k < parsed.size(); k++) {
            auto [x2, y2] = parsed[k];

            auto d = std::abs(x1 - x2) + std::abs(y1 - y2);
            if(d > e1.first) {
                e2 = e1;
                e1 = {d, k};
            } else if(d > e2.first) {
                e2 = {d, k};
            }
            x1 = x2;
            y1 = y2;
        }
    }

    int64_t max = 0;

    test(parsed[e1.second - 1].first > parsed[e1.second].first ? e1.second - 1 : e1.second, parsed.size(), max);
    test(parsed[e2.second - 1].first > parsed[e2.second].first ? e2.second - 1 : e2.second, parsed.size(), max);

    return max;
}

static auto p0 = aoc::test([]() { return (uint64_t)parse().size(); }, 2025, 9, 0, "parse");
static auto p1 = aoc::test(part1, 2025, 9, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 9, 2, "part2");
static auto p2s = aoc::test(part2_shortcut, 2025, 9, 2, "part2_shortcut");

} // namespace y2025::Day9
