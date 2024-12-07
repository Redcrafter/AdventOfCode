#pragma once
#include <array>
#include <iostream>
#include <vector>

#include "../util.hpp"

namespace y2024::Day7 {

const auto input = readFile("../data/2024/day7.txt");

auto parse() {
    std::vector<std::pair<uint64_t, std::vector<uint32_t>>> res;

    size_t i = 0;
    while (i < input.size()) {
        std::vector<uint32_t> vals;

        auto v = readUInt<uint64_t>(input, i);
        i++;

        while (input[i] != '\n') {
            vals.push_back(readUInt<uint32_t>(input, i));
            i--;
        }
        i++;

        res.emplace_back(v, std::move(vals));
    }
    return res;
}
auto lines = parse();

bool test1(const std::vector<uint32_t>& vals, uint64_t res, int i) {
    auto a = vals[i];

    if (i == 1) {
        auto b = vals[i - 1];
        return (a + b == res) || (a * b == res);
    } else {
        return ((res % a) == 0 && test1(vals, res / a, i - 1)) || (res >= a && test1(vals, res - a, i - 1));
    }
}

uint64_t part1() {
    uint64_t result = 0;
    for (auto& [res, vals] : lines) {
        result += res * test1(vals, res, vals.size() - 1);
    }
    return result;
}

uint32_t digits(uint32_t x) {
    uint32_t r = 10;
    while (x >= 10) {
        x /= 10;
        r *= 10;
    }
    return r;
}

bool test2(const std::vector<uint32_t>& vals, uint64_t res, int i) {
    auto a = vals[i];

    if (i == 1) {
        auto b = vals[i - 1];
        return (a + b) == res || (a * b == res) || ((b * digits(a) + a) == res);
    } else {
        if ((res % a) == 0 && test2(vals, res / a, i - 1)) return true;  // reduces a lot and is fast

        auto l = digits(a);
        if (a == (res % l) && test2(vals, res / l, i - 1)) return true;  // reduces a lot and is slow

        return res >= a && test2(vals, res - a, i - 1);  // reduces a little
    }
}

uint64_t part2() {
    uint64_t result = 0;
    for (auto& [res, vals] : lines) {
        result += res * test2(vals, res, vals.size() - 1);
    }
    return result;
}

}  // namespace y2024::Day7
