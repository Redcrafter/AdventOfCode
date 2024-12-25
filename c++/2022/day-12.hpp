#pragma once
#include <array>
#include <unordered_set>

#include "../aoc.hpp"
#include "../util.hpp"
#include "../vec2.hpp"

namespace y2022::Day12 {

auto input_ = split(aoc::getInput(2022, 12), '\n');

auto parseInput() {
    int height = input_.size();
    int width = input_[0].length();

    std::vector<int> dat(width * height);

    for(int y = 0; y < height; y++) {
        auto& line = input_[y];
        if(line.empty()) break;

        for(int x = 0; x < width; x++) {
            dat[x + y * width] = line[x];
        }
    }

    return std::tuple(dat, width, height);
}

const auto [input, width, height] = parseInput();

vec2<int> findEnd() {
    for(size_t i = 0; i < input.size(); i++) {
        if(input[i] == 'E') {
            return {(int)i % width, (int)i / width};
        }
    }
    return {0, 0};
}

template<bool part2>
inline uint64_t bsf() {
    auto end = findEnd();
    auto min = 0;

    std::vector<uint16_t> graph(width * height);
    std::fill(graph.begin(), graph.end(), 65535);

    graph[end.x + end.y * width] = 0;

    std::vector<vec2<int>> heap;
    heap.push_back(end);

    for(size_t pos = 0; pos < heap.size(); pos++) {
        auto currentNode = heap[pos];

        auto x = currentNode.x;
        auto y = currentNode.y;

        auto to = input[x + y * width] - 'a';
        auto score = graph[x + y * width];

        if(to == -28) to = 25;
        if(to == -14) to = 0;

        auto func = [&](int x, int y) {
            auto from = input[x + y * width] - 'a';

            if(from == -28) from = 25;
            if(from == -14) {
                if constexpr(part2) {
                    from = 0;
                } else {
                    min = score + 1;
                    return;
                }
            }

            if(to > from + 1)
                return;
            auto newScore = score + 1;
            auto n = graph[x + y * width];

            if(newScore >= n)
                return;

            if constexpr(part2) {
                if(from == 0) {
                    min = newScore;
                    return;
                }
            }

            graph[x + y * width] = newScore;
            heap.push_back({x, y});
        };

        if(x > 0) func(x - 1, y);
        if(x + 1 < width) func(x + 1, y);
        if(y > 0) func(x, y - 1);
        if(y + 1 < height) func(x, y + 1);

        if(min != 0) return min;
    }

    return min;
}

static auto p1 = aoc::test(bsf<false>, 2022, 12, 1, "part1");
static auto p2 = aoc::test(bsf<true>, 2022, 12, 2, "part2");

} // namespace y2022::Day12
