#pragma once
#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2024::Day22 {

const auto input = extractNumbers<int>(aoc::getInput(2024, 22));

uint64_t part1() {
    uint64_t result = 0;
    for(int i = 0; i < input.size(); i++) {
        auto num = input[i];
        for(int j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = num ^ (num << 11);
        }
        result += num & 0xFFFFFF;
    }
    return result;
}

uint64_t part1_simd() {
    const auto mask = _mm256_set1_epi32(0xFFFFFF);
    uint64_t result = 0;
    alignas(32) int temp[8];

    int i = 0;
    for(; i + 16 <= input.size(); i += 16) {
        auto nums1 = _mm256_loadu_si256((__m256i*)&input[i]);
        auto nums2 = _mm256_loadu_si256((__m256i*)&input[i + 8]);
        for(int j = 0; j < 2000; ++j) {
            nums1 = _mm256_and_si256(_mm256_xor_si256(nums1, _mm256_slli_epi32(nums1, 6)), mask);
            nums2 = _mm256_and_si256(_mm256_xor_si256(nums2, _mm256_slli_epi32(nums2, 6)), mask);
            nums1 = _mm256_xor_si256(nums1, _mm256_srli_epi32(nums1, 5));
            nums2 = _mm256_xor_si256(nums2, _mm256_srli_epi32(nums2, 5));
            nums1 = _mm256_xor_si256(nums1, _mm256_slli_epi32(nums1, 11));
            nums2 = _mm256_xor_si256(nums2, _mm256_slli_epi32(nums2, 11));
        }
        nums1 = _mm256_and_si256(nums1, mask);
        nums2 = _mm256_and_si256(nums2, mask);

        _mm256_store_si256((__m256i*)temp, nums1);
        for(int j = 0; j < 8; ++j)
            result += temp[j];

        _mm256_store_si256((__m256i*)temp, nums2);
        for(int j = 0; j < 8; ++j)
            result += temp[j];
    }

    for(; i < input.size(); i++) {
        auto num = input[i];
        for(int j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = num ^ (num << 11);
        }
        result += num & 0xFFFFFF;
    }
    return result;
}

uint64_t part2() {
    std::array<uint16_t, 1 << 20> possible{};
    std::array<bool, 1 << 20> sub{};
    fixedVector<uint32_t, 2000> is; // keeping track of set indecies is slightly faster than std::bitset

    for(int i = 0; i < input.size(); i++) {
        int num = input[i];
        uint32_t last = num % 10;

        int seq = 0;
        for(int j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = (num ^ (num << 11)) & 0xFFFFFF;

            auto d = num % 10;
            seq = ((seq << 5) + ((d - last) + 9)) & 0xFFFFF;
            last = d;

            if(j >= 3 && !sub[seq]) {
                is.push_back(seq);
                sub[seq] = true;
                possible[seq] += d;
            }
        }

        for(auto i : is)
            sub[i] = 0;
        is.clear();
    }

    return std::ranges::max(possible);
}

static auto p = aoc::test([]() { return extractNumbers<int>(aoc::getInput(2024, 22)).size(); }, 2024, 22, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 22, 1, "part 1");
static auto p1s = aoc::test(part1_simd, 2024, 22, 1, "part 1 simd");
static auto p2 = aoc::test(part2, 2024, 22, 2, "part 2");

} // namespace y2024::Day22
