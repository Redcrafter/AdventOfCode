#pragma once
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2024::Day7 {

const auto input = aoc::getInput(2024, 7);

using vecType = fixedVector<uint16_t, 15>;
using valType = std::pair<vecType, uint64_t>;

auto parse() {
    std::vector<valType> res;
    res.reserve(900);

    size_t i = 0;
    while(i < input.size()) {
        vecType vals;

        auto v = readUInt<uint64_t>(input, i);
        i++;

        while(input[i] != '\n') {
            vals.push_back(readUInt<uint32_t>(input, i));
            i--;
        }
        i++;

        res.emplace_back(vals, v);
    }
    return res;
}
auto lines = parse();

template<int i, int j>
[[clang::always_inline]]
bool static_check1(const vecType& vals, uint64_t a, uint64_t res) {
    auto b = vals[j];
    if constexpr(j == i) {
        return (a + b == res) || (a * b == res);
    } else {
        return static_check1<i, j + 1>(vals, a + b, res) || static_check1<i, j + 1>(vals, a * b, res);
    }
}

bool test1(const vecType& vals, uint64_t res, int i) {
    if(i == 4) return static_check1<4, 1>(vals, vals[0], res);

    auto a = vals[i];
    return ((res % a) == 0 && test1(vals, res / a, i - 1)) || (res >= a && test1(vals, res - a, i - 1));
}

[[clang::always_inline]]
bool test11(const vecType& vals, uint64_t res, int i) {
    if(i == 3) return static_check1<3, 1>(vals, vals[0], res);
    if(i == 2) return static_check1<2, 1>(vals, vals[0], res);
    if(i == 1) return static_check1<1, 1>(vals, vals[0], res);
    return test1(vals, res, vals.size() - 1);
}

uint64_t part1() {
    uint64_t result = 0;
    for(auto& [vals, res] : lines) {
        result += res * test11(vals, res, vals.size() - 1);
    }
    return result;
}

uint32_t digits(uint32_t x) {
    if(x >= 100) return 1000;
    if(x >= 10) return 100;
    return 10;
}

template<int i, int j>
bool static_check2(const vecType& vals, uint64_t a, uint64_t res) {
    auto b = vals[j];
    auto l = digits(b);

    if constexpr(j == i) {
        return (a + b == res) || (a * b == res) || (a * l + b == res);
    } else {
        return static_check2<i, j + 1>(vals, a + b, res) || static_check2<i, j + 1>(vals, a * b, res) || static_check2<i, j + 1>(vals, a * l + b, res);
    }
}

bool test2(const vecType& vals, uint64_t res, int i) {
    if(i == 2) return static_check2<2, 1>(vals, vals[0], res);

    auto a = vals[i];
    auto l = digits(a);
    return (a == (res % l) && test2(vals, res / l, i - 1)) ||
           ((res % a) == 0 && test2(vals, res / a, i - 1)) ||
           (res >= a && test2(vals, res - a, i - 1));
}

uint64_t part2() {
    uint64_t result = 0;
    for(auto& [vals, res] : lines) {
        result += res * (test11(vals, res, vals.size() - 1) || test2(vals, res, vals.size() - 1));
    }
    return result;
}

static auto p = aoc::test([]() { return parse().size(); }, 2024, 7, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 7, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 7, 2, "part2");

} // namespace y2024::Day7
