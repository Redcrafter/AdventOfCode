#pragma once
#include <algorithm>
#include <array>
#include <span>
#include <vector>

#include "../util.hpp"

namespace y2023::Day13 {

const auto input = readFile("../data/2023/day13.txt");

always__inline auto vert1(std::array<uint32_t, 32>& pattern, int height, int ind) {
    if (pattern[ind - 1] != pattern[ind])
        return false;

    auto s = std::min(ind, height - ind);
    for (auto i = 1; i < s; i++) {
        if (pattern[ind - i - 1] != pattern[ind + i])
            return false;
    }
    return true;
}

always__inline auto vert2(std::array<uint32_t, 32>& pattern, int height, int ind) {
    auto err = 0;
    auto s = std::min(ind, height - ind);
    for (auto i = 0; i < s; i++) {
        err += std::popcount(pattern[ind - i - 1] ^ pattern[ind + i]);
    }
    return err == 1;
}

template <auto vFunc>
uint64_t solve() {
    uint64_t result = 0;
    size_t pos = 0;

    std::array<uint32_t, 32> pattern;
    std::array<uint32_t, 32> pattern_f;

    const auto cmp_val = _mm256_set1_epi8('#');
    const auto cmp_val_nl = _mm256_set1_epi8('\n');

    while (pos < input.size()) {
        int width;
        int mask;
        int height = 1;

        {
            auto v = _mm256_loadu_si256((__m256i*)(input.data() + pos));
            width = _tzcnt_u32(_mm256_movemask_epi8(_mm256_cmpeq_epi8(v, cmp_val_nl)));
            mask = (1 << width) - 1;
            pattern[0] = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, cmp_val)) & mask;
        }
        pos += width + 1;

        while (true) {
            // might read beyond the end of the string. oh well
            pattern[height++] = _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)(input.data() + pos)), cmp_val)) & mask;

            pos += width + 1;
            if (pos >= input.size() || input[pos] == '\n') {
                pos++;
                break;
            }
        }

        auto hMask = (1 << height) - 1;
        for (auto j = 1; j < height; j++) {
            if (vFunc(pattern, height, j)) {
                result += j * 100;
                goto end;
            }
        }

        for (size_t i = 0; i < width; i++) {
            uint32_t v = 0;
            for (size_t y = 0; y < 32; y++) {
                if (pattern[y] & (1u << i)) {
                    v |= 1u << y;
                }
            }
            pattern_f[i] = v & hMask;
        }

        for (auto j = 1; j < width; j++) {
            if (vFunc(pattern_f, width, j)) {
                result += j;
                goto end;
            }
        }
    end:
    }

    return result;
}

uint64_t part1() {
    return solve<vert1>();
}

uint64_t part2() {
    return solve<vert2>();
}

}  // namespace y2023::Day13
