#pragma once
#include "../aoc.hpp"
#include "../util.hpp"

namespace y2021::Day7 {

const auto input = extractNumbers<int>(aoc::getInput(2021, 7));

template<int part>
uint64_t func() {
    static_assert(part == 1 || part == 2, "invalid day");

    auto [min, max] = std::ranges::minmax_element(input);

    uint32_t best = -1;
    for(int i = *min; i < *max; i++) {
        uint32_t cost = 0;
        for(size_t j = 0; j < input.size(); j++) {
            auto val = std::abs(input[j] - i);
            if(part == 1) {
                cost += val;
            } else if(part == 2) {
                cost += (val * (val + 1)) / 2;
            }
        }

        if(cost < best)
            best = cost;
        else
            break;
    }
    return best;
}

static auto p1 = aoc::test(func<1>, 2021, 7, 1, "part1");
static auto p2 = aoc::test(func<2>, 2021, 7, 2, "part2");

} // namespace y2021::Day7
