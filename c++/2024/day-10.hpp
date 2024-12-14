#pragma once
#include <array>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day10 {

const auto input = aoc::getInput(2024, 10);

const int width = 43;
const int height = 43;

// tempalte is used to skip going back to the previous position
template<int dx, int dy, int h>
int count1(int x, int y, std::array<bool, width * height>& visited) {
    if(visited[x + y * width]) return 0;
    visited[x + y * width] = true;

    if constexpr(h == '9') {
        return 1;
    } else {

        int result = 0;
        if(dx !=  1 && x > 0          && input[x - 1 + y       * (width + 1)] == h + 1) result += count1<-1,  0, h + 1>(x - 1, y, visited);
        if(dx != -1 && x + 1 < width  && input[x + 1 + y       * (width + 1)] == h + 1) result += count1< 1,  0, h + 1>(x + 1, y, visited);
        if(dy !=  1 && y > 0          && input[x     + (y - 1) * (width + 1)] == h + 1) result += count1< 0, -1, h + 1>(x, y - 1, visited);
        if(dy != -1 && y + 1 < height && input[x     + (y + 1) * (width + 1)] == h + 1) result += count1< 0,  1, h + 1>(x, y + 1, visited);
        return result;
    }
}

uint64_t part1() {
    uint64_t result = 0;
    std::array<bool, width * height> visited;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(input[x + y * (width + 1)] == '0') {
                visited.fill(false);
                result += count1<0, 0, '0'>(x, y, visited);
            }
        }
    }

    return result;
}

template<int dx, int dy, int h>
int count2(int x, int y, std::array<int8_t, width * height>& known) {
    if constexpr(h == '9') {
        return 1;
    } else {
        auto v = known[x + y * width];
        if(v != -1) return v;

        int result = 0;
        if(dx !=  1 && x > 0          && input[x - 1 + y       * (width + 1)] == h + 1) result += count2<-1,  0, h + 1>(x - 1, y, known);
        if(dx != -1 && x + 1 < width  && input[x + 1 + y       * (width + 1)] == h + 1) result += count2< 1,  0, h + 1>(x + 1, y, known);
        if(dy !=  1 && y > 0          && input[x     + (y - 1) * (width + 1)] == h + 1) result += count2< 0, -1, h + 1>(x, y - 1, known);
        if(dy != -1 && y + 1 < height && input[x     + (y + 1) * (width + 1)] == h + 1) result += count2< 0,  1, h + 1>(x, y + 1, known);
        known[x + y * width] = result;
        return result;
    }
}

uint64_t part2() {
    uint64_t result = 0;
    std::array<int8_t, width * height> known;
    known.fill(-1);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(input[x + y * (width + 1)] == '0') {
                result += count2<0, 0, '0'>(x, y, known);
            }
        }
    }

    return result;
}

static auto p1 = aoc::test(part1, 2024, 10, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 10, 2, "part2");

} // namespace y2024::Day10
