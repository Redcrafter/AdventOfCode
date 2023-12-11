#pragma once
#include <emmintrin.h>
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <vector>

#include "../util.hpp"

namespace y2023::Day11 {

const auto input = readFile("../data/2023/day11.txt");

uint64_t solve_old(uint32_t add) {
    add--;

    const auto cmp_val_256 = _mm256_set1_epi8('#');
    const auto cmp_val_128 = _mm_set1_epi8('#');
    const auto cmp_mask_128 = _mm_set_epi64x(0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

    std::vector<Point<int32_t>> galac;

    size_t pos = 0;
    uint32_t height = 0;
    uint32_t y_offset = 0;
    while (pos < input.size()) {
        bool ok = true;
        for (size_t i = 0; i < 4; i++) {
            auto v = _mm256_loadu_si256((__m256i *)(input.data() + pos));
            auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, cmp_val_256));
            pos += 32;
            ok &= mask == 0;

            while (mask != 0) {
                auto x = _tzcnt_u32(mask);
                mask &= ~(1 << x);
                galac.emplace_back(x + i * 32, y_offset);
            }
        }

        {
            auto v = _mm_loadu_si128((__m128i *)(input.data() + pos));
            auto val = _mm_and_si128(v, cmp_mask_128);
            auto mask = _mm_movemask_epi8(_mm_cmpeq_epi8(val, cmp_val_128));

            while (mask != 0) {
                auto x = _tzcnt_u32(mask);
                mask &= ~(1 << x);
                galac.emplace_back(x + 128, y_offset);
            }
        }

        pos += 13;
        height++;
        y_offset++;
        if (ok) y_offset += add;
    }

    for (int x = 140 - 1; x >= 0; x--) {
        auto ok = true;
        for (int y = 0; y < 140; y++) {
            ok &= input[x + y * 141] != '#';
        }
        if (ok) {
            for (auto &g : galac) {
                g.x += (g.x > x) * add;
            }
        }
    }

    int64_t res = 0;
    for (int i = 0; i < galac.size(); i++) {
        const auto a = galac[i];

        for (int j = i + 1; j < galac.size(); j++) {
            const auto b = galac[j];
            res += std::abs(a.x - b.x);
            res += std::abs(a.y - b.y);
        }
    }
    return res;
}

// works for all input sizes
uint64_t solve_general(int64_t add) {
    const auto cmp_val_256 = _mm256_set1_epi8('#');

    size_t pos = 0;
    int32_t _count = 0;

    const uint8_t size = findChar(input.data(), '\n') + 1;
    std::vector<Point<int32_t>> data(size - 1);
    std::fill(data.begin(), data.end(), Point(0));

    while (pos < input.size()) {
        auto v = _mm256_loadu_si256((__m256i *)(input.data() + pos));
        auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, cmp_val_256));

        while (mask != 0) {
            auto p = _tzcnt_u32(mask);
            mask &= ~(1 << p);

            auto id = pos + p;
            data[id % size].x++;
            data[id / size].y++;
            _count++;
        }

        pos += 32;
    }

    int64_t score = 0;
    Point count = {0, 0};
    Point rmn = Point(_count) - count;

    for (size_t i = 0; i < data.size(); i++) {
        score += rmn.x * count.x * ((data[i].x == 0) ? add : 1);
        score += rmn.y * count.y * ((data[i].y == 0) ? add : 1);

        count += data[i];
        rmn -= data[i];
    }

    return score;
}

uint64_t solve(int64_t add) {
    const auto cmp_val_256 = _mm256_set1_epi8('#');
    const auto cmp_val_128 = _mm_set1_epi8('#');
    const auto cmp_mask_128 = _mm_set_epi64x(0xFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

    // specialized for 140x140 input
    std::array<Point<int32_t>, 140> data;
    data.fill({0, 0});

    size_t pos = 0;
    int32_t _count = 0;
    int32_t height = 0;
    while (pos < input.size()) {
        for (size_t i = 0; i < 4; i++) {
            auto v = _mm256_loadu_si256((__m256i *)(input.data() + pos));
            auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(v, cmp_val_256));
            pos += 32;

            while (mask != 0) {
                auto x = _tzcnt_u32(mask);
                mask &= ~(1 << x);
                data[x + i * 32].x++;
                data[height].y++;
                _count++;
            }
        }

        {
            auto v = _mm_loadu_si128((__m128i *)(input.data() + pos));
            auto mask = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_and_si128(v, cmp_mask_128), cmp_val_128));
            pos += 13;

            while (mask != 0) {
                auto x = _tzcnt_u32(mask);
                mask &= ~(1 << x);
                data[x + 128].x++;
                data[height].y++;
                _count++;
            }
        }

        height++;
    }

    int64_t score = 0;
    Point count = {0, 0};
    Point rmn = Point(_count) - count;

    for (size_t i = 0; i < data.size(); i++) {
        score += rmn.x * count.x * ((data[i].x == 0) ? add : 1);
        score += rmn.y * count.y * ((data[i].y == 0) ? add : 1);

        count += data[i];
        rmn -= data[i];
    }

    return score;
}

uint64_t part1_old() {
    return solve_old(2);
}

uint64_t part2_old() {
    return solve_old(1000000);
}

uint64_t part1_general() {
    return solve_general(2);
}

uint64_t part2_general() {
    return solve_general(1000000);
}

uint64_t part1() {
    return solve(2);
}

uint64_t part2() {
    return solve(1000000);
}

}  // namespace y2023::Day11
