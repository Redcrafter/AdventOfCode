#pragma once
#include <array>
#include <vector>

#include "../aoc.hpp"
#include "../fixedVector.hpp"

namespace y2024::Day25 {

const auto input = aoc::getInput(2024, 25);

uint64_t part1() {
    std::vector<std::array<uint8_t, 5>> keys;
    std::vector<std::array<uint8_t, 5>> locks;

    for(size_t i = 0; i < input.size(); i += 43) {
        std::array<uint8_t, 5> v;
        v.fill(0);

        for(int y = 0; y < 7; y++) {
            for(int x = 0; x < 5; x++) {
                v[x] += input[x + y * 6 + i] == '#';
            }
        }

        if(input[i] == '#') {
            keys.push_back(v);
        } else {
            locks.push_back(v);
        }
    }

    int result = 0;

    for(auto& key : keys) {
        for(auto& lock : locks) {
            auto ok = true;
            for(int i = 0; i < key.size(); i++) {
                if(key[i] + lock[i] > 7) {
                    ok = false;
                }
            }
            if(ok) {
                result++;
            }
        }
    }

    return result;
}

uint64_t part1_bit() {
    fixedVector<uint32_t, 250> keys;
    fixedVector<uint32_t, 250> locks;

    for(size_t i = 0; i < input.size(); i += 43) {
        uint32_t v = 0;

        for(int j = 6; j < 36; j++) {
            v += (input[j + i] == '#') << (j - 6);
        }

        if(input[i] == '#') {
            keys.push_back(v);
        } else {
            locks.push_back(v);
        }
    }

    int result = 0;
    for(size_t i = 0; i < 250; i++) {
        for(size_t j = 0; j < 250; j++) {
            result += (keys[i] & locks[j]) == 0;
        }
    }
    return result;
}

static auto p1 = aoc::test(part1, 2024, 25, 1, "part 1");
static auto p1b = aoc::test(part1_bit, 2024, 25, 1, "part 1 bit");

} // namespace y2024::Day25
