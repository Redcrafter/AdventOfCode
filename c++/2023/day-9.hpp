#pragma once
#include <algorithm>
#include <array>
#include <vector>

#include "../util.hpp"

namespace y2023::Day9 {

const auto input = readFile("../data/2023/day9.txt");
constexpr int size = 32;

always__inline auto readLine(size_t& pos, std::array<int32_t, size>& arr) {
    int asd = 0;

    while (true) {
        char c = input[pos];
        int n = 0;
        int s = 1;

        if (c == '-') {
            c = input[++pos];
            s = -1;
        }
        while (isDigit(c)) {
            n = n * 10 + (c - '0');
            c = input[++pos];
        }
        pos++;
        arr[asd++] = n * s;
        if (c == '\n') {
            break;
        }
    }
    return asd;
}

always__inline auto calcStack(size_t& pos, std::array<std::array<int32_t, size>, size>& stack) {
    auto asd = readLine(pos, stack[0]);

    int i = 0;
    while (true) {
        auto& last = stack[i];
        i++;
        auto& n = stack[i];

        auto s = asd - i;
        for (int j = 0; j < s; j++) {
            n[j] = last[j + 1] - last[j];
        }

        bool b = true;
        auto v = n[0];
        for (size_t j = 0; j < s; j++) {
            b &= n[j] == v;
        }
        if (b) break;
    }

    return i;
}

uint64_t part1() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<std::array<int32_t, size>, size> stack;

    while (pos < input.size()) {
        auto i = calcStack(pos, stack);

        for (; i >= 0; i--) {
            result += stack[i][20 - i];
        }
    }

    return result;
}

uint64_t part2() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<std::array<int32_t, size>, size> stack;

    while (pos < input.size()) {
        auto i = calcStack(pos, stack);

        auto v = stack[i][0];
        for (int j = i - 1; j >= 0; j--) {
            v = stack[j][0] - v;
        }
        result += v;
    }

    return result;
}

constexpr auto genTable() {
    std::array<std::array<int, 32>, 32> res;

    for (size_t i = 0; i < 32; i++) {
        int c = 1;
        for (int j = 0; j < i + 1; j++) {
            res[i][j] = c;
            c = c * (i - j) / (j + 1);
        }
    }

    return res;
}

// precompute Binomial coefficients to speed up calculation
auto table = genTable();

// see https://en.wikipedia.org/wiki/Polynomial_interpolation#Interpolations_as_linear_combinations_of_values
uint64_t part1_math() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<int32_t, size> arr;

    while (pos < input.size()) {
        auto size = readLine(pos, arr);
        int s = 0;
        for (size_t i = 0; i < size; i++) {
            s = table[size][i] * arr[i] - s;
        }
        result += s;
    }

    return result;
}

uint64_t part2_math() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<int32_t, size> arr;

    while (pos < input.size()) {
        auto size = readLine(pos, arr);

        int s = 0;
        for (size_t i = 0; i < size; i++) {
            s = table[size][i] * arr[size - i - 1] - s;
        }
        result += s;
    }

    return result;
}

}  // namespace y2023::Day9
