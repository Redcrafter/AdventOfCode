#pragma once
#include <cmath>
#include <print>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2025::Day6 {

const auto input = aoc::getInput(2025, 6);

uint64_t part1() {
    uint64_t res = 0;

    auto len = input.find_first_of('\n');
    size_t pos = 0;
    std::array<int, 4> nums;

    while(pos < input.length() / 5) {
        auto op = input[pos + 4 * (len + 1)];

        nums.fill(0);
        auto done = false;
        while(!done) {
            done = true;
            for(size_t i = 0; i < 4; i++) {
                auto c = input[pos + i * (len + 1)];
                if(isDigit(c)) {
                    nums[i] = nums[i] * 10 + c - '0';
                    done = false;
                }
            }
            pos++;
        }

        if(op == '+') {
            res += nums[0] + nums[1] + nums[2] + nums[3];
        } else {
            res += (uint64_t)nums[0] * nums[1] * nums[2] * nums[3];
        }
    }

    return res;
}

uint64_t part2() {
    uint64_t res = 0;

    auto len = input.find_first_of('\n');
    size_t pos = 0;
    fixedVector<int, 4> nums;

    while(pos < input.length() / 5) {
        auto op = input[pos + 4 * (len + 1)];

        nums.clear();
        while(true) {
            int n = 0;
            for(size_t i = 0; i < 4; i++) {
                auto c = input[pos + i * (len + 1)];
                if(isDigit(c)) {
                    n = n * 10 + c - '0';
                }
            }
            pos++;
            if(n == 0) break;
            nums.push_back(n);
        }

        if(op == '+') {
            res += sum<int, int>(nums);
        } else {
            res += prod<uint64_t, int>(nums);
        }
    }

    return res;
}

static auto p1 = aoc::test(part1, 2025, 6, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 6, 2, "part2");

} // namespace y2025::Day6
