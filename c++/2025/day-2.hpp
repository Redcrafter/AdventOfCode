#pragma once
#include <cmath>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2025::Day2 {

const auto input = aoc::getInput(2025, 2);

auto parse() {
    size_t pos = 0;
    fixedVector<std::pair<int64_t, int64_t>, 48> res;
    while(pos + 1 < input.length()) {
        auto a = readUInt<int64_t>(input, pos);
        auto b = readUInt<int64_t>(input, pos);
        res.push_back({a, b});
    }
    return res;
}

auto parsed = parse();

int64_t pow10(int n) {
    constexpr int64_t pow10[] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
        10000000000,
        100000000000,
        1000000000000,
        10000000000000,
        100000000000000,
        1000000000000000,
        10000000000000000,
        100000000000000000,
        1000000000000000000,
    };
    return pow10[n];
}

int int_log2(uint64_t x) { return 63 - std::countl_zero(x | 1); }

int digit_count(uint64_t x) {
    constexpr uint64_t table[] = {
        9,
        99,
        999,
        9999,
        99999,
        999999,
        9999999,
        99999999,
        999999999,
        9999999999,
        99999999999,
        999999999999,
        9999999999999,
        99999999999999,
        999999999999999ull,
        9999999999999999ull,
        99999999999999999ull,
        999999999999999999ull,
        9999999999999999999ull,
    };
    int y = (19 * int_log2(x) >> 6);
    return y + (x > table[y]) + 1;
}

int64_t count_range(int64_t min, int64_t max, int64_t step) {
    auto first = (min + step - 1) / step;
    auto last = max / step;
    if(last < first) return 0;

    return (step * (last - first + 1) * (last + first)) / 2;
}

uint64_t part1() {
    uint64_t res = 0;

    for(auto [a, b] : parsed) {
        auto len = digit_count(b) & ~1;

        auto min = std::max(pow10(len - 1), a);
        auto max = std::min(pow10(len) - 1, b);

        // auto step = 1 + pow10(len / 2);
        // res += count_range(min, max, step);

        switch(len) {
            case  2: res += count_range(min, max,     11); break;
            case  4: res += count_range(min, max,    101); break;
            case  6: res += count_range(min, max,   1001); break;
            case  8: res += count_range(min, max,  10001); break;
            case 10: res += count_range(min, max, 100001); break;
        }
    }

    return res;
}

uint64_t part2() {
    uint64_t res = 0;

    for(auto [a, b] : parsed) {
        auto len = digit_count(a);
        int64_t min = pow10(len - 1);
        int64_t max = pow10(len) - 1;

        while(b >= min) {
            auto min1 = std::max(a, min);
            auto max1 = std::min(b, max);

            switch(len) {
                case 2: res += count_range(min1, max1, 11); break;
                case 3: res += count_range(min1, max1, 111); break;
                case 4: res += count_range(min1, max1, 101); break;
                case 5: res += count_range(min1, max1, 11111); break;
                case 6:
                    res += count_range(min1, max1, 1001);
                    res += count_range(min1, max1, 10101);
                    res -= count_range(min1, max1, 111111);
                    break;
                case 7: res += count_range(min1, max1, 1111111); break;
                case 8: res += count_range(min1, max1, 10001); break;
                case 9: res += count_range(min1, max1, 1001001); break;
                case 10:
                    res += count_range(min1, max1, 100001);
                    res += count_range(min1, max1, 101010101);
                    res -= count_range(min1, max1, 1111111111);
                    break;
            }

            len++;
            min *= 10;
            max = max * 10 + 9;
        }
    }

    return res;
}

static auto p0 = aoc::test([]() { return (uint64_t)parse().size(); }, 2025, 2, 0, "parse");
static auto p1 = aoc::test(part1, 2025, 2, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 2, 2, "part2");

} // namespace y2025::Day2
