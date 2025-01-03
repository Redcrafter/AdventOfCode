#pragma once
#include <array>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2023::Day9 {

const auto input = aoc::getInput(2023, 9);
constexpr int size = 32;

always__inline auto readLine(size_t& pos, std::array<int32_t, size>& arr) {
    int asd = 0;

    while(true) {
        char c = input[pos];
        int n = 0;

        if(c == '-') {
            c = input[++pos];

            while(isDigit(c)) {
                n = n * 10 + (c - '0');
                c = input[++pos];
            }
            arr[asd++] = -n;
        } else {
            while(isDigit(c)) {
                n = n * 10 + (c - '0');
                c = input[++pos];
            }
            arr[asd++] = n;
        }
        pos++;
        if(c == '\n') {
            break;
        }
    }
    return asd;
}

always__inline auto calcStack(size_t& pos, std::array<std::array<int32_t, size>, size>& stack) {
    auto asd = readLine(pos, stack[0]);

    int i = 0;
    while(true) {
        auto& last = stack[i];
        i++;
        auto& n = stack[i];

        auto s = asd - i;
        for(int j = 0; j < s; j++) {
            n[j] = last[j + 1] - last[j];
        }

        bool b = true;
        auto v = n[0];
        for(int j = 0; j < s; j++) {
            b &= n[j] == v;
        }
        if(b) break;
    }

    return i;
}

uint64_t part1() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<std::array<int32_t, size>, size> stack;

    while(pos < input.size()) {
        auto i = calcStack(pos, stack);

        for(; i >= 0; i--) {
            result += stack[i][20 - i];
        }
    }

    return result;
}

uint64_t part2() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<std::array<int32_t, size>, size> stack;

    while(pos < input.size()) {
        auto i = calcStack(pos, stack);

        auto v = stack[i][0];
        for(int j = i - 1; j >= 0; j--) {
            v = stack[j][0] - v;
        }
        result += v;
    }

    return result;
}

constexpr auto genTable() {
    std::array<std::array<int, 32>, 32> res;

    for(int i = 0; i < 32; i++) {
        int c = 1;
        for(int j = 0; j < i + 1; j++) {
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

    while(pos < input.size()) {
        auto size = readLine(pos, arr);
        int s = 0;
        for(int i = 0; i < size; i++) {
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

    while(pos < input.size()) {
        auto size = readLine(pos, arr);

        int s = 0;
        for(int i = 0; i < size; i++) {
            s = table[size][i] * arr[size - i - 1] - s;
        }
        result += s;
    }

    return result;
}

// all lines can be summed togther so we have to compute the continuation only once
uint64_t part1_sum() {
    size_t pos = 0;

    std::array<int32_t, size> arr;
    std::array<int64_t, size> sum;
    sum.fill(0);

    int size;
    while(pos < input.size()) {
        size = readLine(pos, arr);
        for(int i = 0; i < size; i++) {
            sum[i] += arr[i];
        }
    }

    int64_t result = 0;
    for(int i = 0; i < size; i++) {
        result = table[size][i] * sum[i] - result;
    }
    return result;
}

uint64_t part2_sum() {
    size_t pos = 0;

    std::array<int32_t, size> arr;
    std::array<int64_t, size> sum;
    sum.fill(0);

    int size;
    while(pos < input.size()) {
        size = readLine(pos, arr);

        for(int i = 0; i < size; i++) {
            sum[i] += arr[i];
        }
    }

    int64_t result = 0;
    for(int i = 0; i < size; i++) {
        result = table[size][i] * sum[size - i - 1] - result;
    }
    return result;
}

static auto p1 = aoc::test(part1, 2023, 9, 1, "part1");
static auto p1m = aoc::test(part1_math, 2023, 9, 1, "part1_math");
static auto p1s = aoc::test(part1_sum, 2023, 9, 1, "part1_sum");

static auto p2 = aoc::test(part2, 2023, 9, 2, "part2");
static auto p2m = aoc::test(part2_math, 2023, 9, 2, "part2_math");
static auto p2s = aoc::test(part2_sum, 2023, 9, 2, "part2_sum");

} // namespace y2023::Day9
