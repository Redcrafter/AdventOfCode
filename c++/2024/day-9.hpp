#pragma once
#include <array>
#include <vector>

#include "../aoc.hpp"

namespace y2024::Day9 {

const auto input = trimEnd(aoc::getInput(2024, 9));

int64_t triangle(int64_t n) {
    return (n * (n + 1)) / 2;
}

uint64_t part1() {
    uint64_t result = 0;

    int lIndex = 0;
    int rIndex = input.size() - 1;
    int lGap = 0;

    int rVal = 0;
    int rSize = 0;

    int ind = 0;

    auto add = [&](int value, int times) {
        result += value * (triangle(ind + times - 1) - triangle(ind - 1));
        ind += times;
    };

    while(lIndex < rIndex) {
        if(lGap == 0) { // ran out of gap
            auto v = input[lIndex] & 0xF;
            add(lIndex / 2, v);
            lIndex++;

            lGap = input[lIndex] & 0xF;
            lIndex++;
        }
        if(rSize == 0) { // ran out of right value
            rSize = input[rIndex] & 0xF;
            rVal = rIndex / 2;
            rIndex -= 2;
        }

        auto n = std::min(rSize, lGap);
        add(rVal, n);
        rSize -= n;
        lGap -= n;
    }

    add(lIndex / 2, input[lIndex] & 0xF);
    add(rVal, rSize);

    return result;
}

uint64_t part2() {
    std::array<std::vector<uint32_t>, 10> gaps;

    uint32_t size = 0;
    for(size_t i = 0; i < input.size();) {
        size += input[i] & 0xF;
        i++;
        if(i >= input.size()) break;

        auto g = input[i] & 0xF;
        i++;
        if(g == 0) continue;

        gaps[g].push_back(size);
        size += g;
    }

    for(auto&& el : gaps)
        std::reverse(el.begin(), el.end());

    uint64_t result = 0;
    auto add = [&](int value, int times, int ind) {
        result += value * (triangle(ind + times - 1) - triangle(ind - 1));
    };

    int i = input.size() - 1;
    auto offset = size;
    while(i >= 0) {
        auto size = input[i] & 0xF;
        offset -= size;
        auto nOffset = offset;
        auto val = i / 2;
        i--;

        if(i >= 0) {
            offset -= input[i] & 0xF;
            i--;
        }
        if(size == 0) continue;

        auto minG = 1u << 30;
        auto minGapSize = -1;

        for(size_t j = size; j < gaps.size(); j++) {
            auto& g = gaps[j];
            if(g.size() == 0) continue;
            auto gi = g[g.size() - 1];

            if(gi < minG) {
                minG = gi;
                minGapSize = j;
            }
        }

        if(minGapSize == -1 || minG > nOffset) {
            add(val, size, nOffset);
        } else {
            add(val, size, minG);

            gaps[minGapSize].pop_back();
            if(minGapSize > size) {
                auto& g = gaps[minGapSize - size];
                auto p = minG + size;

                g.push_back(p);
                for(int i = g.size() - 2; i >= 0; i--) {
                    if(g[i] > p) {
                        g[i + 1] = p;
                        break;
                    } else {
                        g[i + 1] = g[i];
                    }
                }
            }
        }
    }

    return result;
}

static auto p1 = aoc::test(part1, 2024, 9, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 9, 2, "part2");

} // namespace y2024::Day9
