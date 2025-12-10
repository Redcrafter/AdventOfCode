#pragma once
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2025::Day10 {

const auto input = aoc::getInput(2025, 10);

struct line {
    std::string_view light;
    std::vector<std::vector<int>> moves;
    std::vector<int> joltage;
};

auto parse() {
    std::vector<line> lines;

    size_t pos = 0;
    while(pos < input.length()) {
        line item;
        {
            pos++;
            auto end = input.find_first_of(']', pos);
            item.light = input.substr(pos, (end - pos));
            pos = end + 2;
        }

        while(true) {
            pos++;
            std::vector<int> moves;

            while(isDigit(input[pos])) {
                moves.push_back(readUInt(input, pos));
            }

            if(input[pos++] == '\n') { // last item is joltage
                item.joltage = moves;
                break;
            } else {
                item.moves.push_back(std::move(moves));
            }
        }

        lines.push_back(std::move(item));
    }

    return lines;
}

const auto parsed = parse();

uint64_t part1() {
    int res = 0;
    std::array<uint8_t, 1 << 10> known;
    std::vector<int> moves;

    std::vector<int> curr;
    std::vector<int> next;

    for(const auto& item : parsed) {
        moves.clear();
        for(const auto& move : item.moves) {
            int n = 0;
            for (auto i : move) {
                n |= 1 << i;
            }
            moves.push_back(n);
        }

        int target = 0;
        for(size_t i = 0; i < item.light.size(); i++) {
            if(item.light[i] == '#')
                target |= 1 << i;
        }

        known.fill(0);
        known[0] = 1;

        curr.clear();
        curr.push_back(0);

        for(size_t i = 1;; i++) {
            next.clear();

            for(int state : curr) {
                for(int move : moves) {
                    auto val = state ^ move;
                    if(val == target) {
                        res += i;
                        goto end;
                    }

                    if(!known[val]) {
                        known[val] = 1;
                        next.push_back(val);
                    }
                }
            }
            std::swap(next, curr);
        }

    end:
    }

    return res;
}

// see js solution using z3
uint64_t part2() {
    return 0;
}

static auto p0 = aoc::test([]() { return (uint64_t)parse().size(); }, 2025, 10, 0, "parse");
static auto p1 = aoc::test(part1, 2025, 10, 1, "part1");
// static auto p2 = aoc::test(part2, 2025, 10, 2, "part2");

} // namespace y2025::Day10
