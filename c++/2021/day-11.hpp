#pragma once
#include <array>

namespace Day11 {

std::array<uint8_t, 256> parseData() {
    std::array<uint8_t, 256> data;

    auto input = readLines("../data/2021/day11.txt");

    for (size_t y = 0; y < 10; y++) {
        for (size_t x = 0; x < 10; x++) {
            int val = input[y][x] - '0';
            data[(x + 1) + (y + 1) * 16] = val;
        }
    }
    return data;
}

const auto inp = parseData();

template <int part>
uint64_t func() {
    static_assert(part == 1 || part == 2, "invalid day");

    auto input = inp;

    int stackId = 0;
    std::array<int, 256> stack;

    int resetId = 0;
    std::array<int, 256> reset;

    int flashes = 0;

    for (int i = 0; part == 2 || i < 100; i++) {
        for (int j = 0; j < 192; j++) {
            input[j]++;
        }

#pragma clang loop unroll(full)
        for (int y = 1; y <= 10; y++) {
#pragma clang loop unroll(full)
            for (int x = 1; x <= 10; x++) {
                int j = x + (y << 4);
                if (input[j] > 9) {
                    reset[resetId++] = j;

                    if (input[j - 1 - 16]++ == 9) stack[stackId++] = j - 1 - 16;
                    if (input[j + 0 - 16]++ == 9) stack[stackId++] = j + 0 - 16;
                    if (input[j + 1 - 16]++ == 9) stack[stackId++] = j + 1 - 16;
                    if (input[j - 1]++ == 9) stack[stackId++] = j - 1;

                    input[j + 1]++;
                    input[j - 1 + 16]++;
                    input[j + 0 + 16]++;
                    input[j + 1 + 16]++;
                }
            }
        }

        while (stackId > 0) {
            auto ind = stack[--stackId];
            int x = ind & 0xF;
            int y = ind >> 4;
            if (x < 1 || x > 10 || y < 1 || y > 10) continue;

            reset[resetId++] = ind;

            if (input[ind - 1 - 16]++ == 9) stack[stackId++] = ind - 1 - 16;
            if (input[ind + 0 - 16]++ == 9) stack[stackId++] = ind + 0 - 16;
            if (input[ind + 1 - 16]++ == 9) stack[stackId++] = ind + 1 - 16;
            if (input[ind - 1]++ == 9) stack[stackId++] = ind - 1;
            if (input[ind + 1]++ == 9) stack[stackId++] = ind + 1;
            if (input[ind - 1 + 16]++ == 9) stack[stackId++] = ind - 1 + 16;
            if (input[ind + 0 + 16]++ == 9) stack[stackId++] = ind + 0 + 16;
            if (input[ind + 1 + 16]++ == 9) stack[stackId++] = ind + 1 + 16;
        }

        if (part == 1) {
            flashes += resetId;
        } else if (part == 2) {
            if (resetId == 100) return i + 1;
        }

        while (resetId > 0) {
            input[reset[--resetId]] = 0;
        }
    }

    return flashes;
}

}  // namespace Day11
