#pragma once
#include <unordered_map>
#include <utility>

#include "../aoc.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2024::Day21 {

const auto input = aoc::getInput(2024, 21);

vec2<int8_t> mapKey(char c) {
    switch(c) {
        case '7': return {0, 0};
        case '4': return {0, 1};
        case '1': return {0, 2};
        case '0': return {1, 3};
        case '8': return {1, 0};
        case '5': return {1, 1};
        case '2': return {1, 2};
        case 'A': return {2, 3};
        case '9': return {2, 0};
        case '6': return {2, 1};
        case '3': return {2, 2};
    }
    std::unreachable();
}

vec2<int8_t> mapDir(char c) {
    switch(c) {
        case '^': return {1, 0};
        case 'A': return {2, 0};
        case '<': return {0, 1};
        case 'v': return {1, 1};
        case '>': return {2, 1};
    }
    std::unreachable();
}

template<int layer, int nlayer>
uint64_t shortest(char start_, char end_, std::unordered_map<uint32_t, uint64_t>& cache) {
    if constexpr(layer == 0)
        return 1;
    else {
        if(start_ == end_) return 1;

        if constexpr(nlayer != 3) {
            auto cached = cache[start_ | (end_ << 8) | (layer << 16)];
            if(cached != 0) return cached;
        }

        vec2<int8_t> start, end;
        if constexpr(layer == nlayer) {
            start = mapKey(start_);
            end = mapKey(end_);
        } else {
            start = mapDir(start_);
            end = mapDir(end_);
        }

        char vert = 0, hori = 0;
        if(end.y < start.y) vert = '^';
        else if(end.y > start.y) vert = 'v';

        if(end.x < start.x) hori = '<';
        else if(end.x > start.x) hori = '>';

        uint64_t retVal = 0;

        auto d = (end - start).abs() - 1;

        if(start.x == end.x)
            retVal = d.y + shortest<layer - 1, nlayer>('A', vert, cache) + shortest<layer - 1, nlayer>(vert, 'A', cache);
        else if(start.y == end.y)
            retVal = d.x + shortest<layer - 1, nlayer>('A', hori, cache) + shortest<layer - 1, nlayer>(hori, 'A', cache);
        else {
            if(start.x == 0 && (layer < nlayer || end.y == 3))
                retVal = d.x + d.y + shortest<layer - 1, nlayer>('A', hori, cache) + shortest<layer - 1, nlayer>(hori, vert, cache) + shortest<layer - 1, nlayer>(vert, 'A', cache);
            else if(end.x == 0 && (layer < nlayer || start.y == 3))
                retVal = d.x + d.y + shortest<layer - 1, nlayer>('A', vert, cache) + shortest<layer - 1, nlayer>(vert, hori, cache) + shortest<layer - 1, nlayer>(hori, 'A', cache);
            else
                retVal = d.x + d.y + std::min(
                    shortest<layer - 1, nlayer>('A', hori, cache) + shortest<layer - 1, nlayer>(hori, vert, cache) + shortest<layer - 1, nlayer>(vert, 'A', cache), 
                    shortest<layer - 1, nlayer>('A', vert, cache) + shortest<layer - 1, nlayer>(vert, hori, cache) + shortest<layer - 1, nlayer>(hori, 'A', cache)
                );
        }
        if constexpr(nlayer != 3)
            cache[start_ | (end_ << 8) | (layer << 16)] = retVal;
        return retVal;
    }
}

template<int N>
uint64_t solve() {
    std::unordered_map<uint32_t, uint64_t> cache;

    uint64_t res = 0;
    for(int i = 0; i < 5; i++) {
        auto str = input.substr(i * 5, 4);

        uint64_t v = 0;
        for(int j = 0; j < 4; j++) {
            v += shortest<N + 1, N + 1>(str[(j + 3) % 4], str[j], cache);
        }
        res += readExactInt<int, 3>(str) * v;
    }
    return res;
}

uint64_t part1() {
    return solve<2>();
}

uint64_t part2() {
    return solve<25>();
}

static auto p1 = aoc::test(part1, 2024, 21, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 21, 2, "part 2");

} // namespace y2024::Day21
