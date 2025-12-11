#pragma once
#include <unordered_map>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2025::Day11 {

const auto input = aoc::getInput(2025, 11);

struct line {
    int16_t src;
    std::vector<int16_t> dst;
};

constexpr int16_t read_compress(std::string_view str, size_t pos = 0) {
    return (str[pos + 0] - 'a') +
           (str[pos + 1] - 'a') * 26 +
           (str[pos + 2] - 'a') * 26 * 26;
}

auto parse() {
    std::array<std::vector<int16_t>, 26 * 26 * 26> res{};

    size_t pos = 0;
    while(pos < input.length()) {
        auto first = read_compress(input, pos);
        pos += 4;

        auto& vec = res[first];
        while(input[pos++] != '\n') {
            vec.emplace_back(read_compress(input, pos));
            pos += 3;
        }
    }

    return res;
}

const auto parsed = parse();

auto visit1(uint16_t node, std::array<int, 26 * 26 * 26>& visited) {
    if(visited[node]) return visited[node];

    int res = 0;
    for(const auto& item : parsed[node]) {
        res += visit1(item, visited);
    }
    visited[node] = res;
    return res;
}

uint64_t part1() {
    std::array<int, 26 * 26 * 26> visited{};
    visited[read_compress("out")] = 1;
    return visit1(read_compress("you"), visited);
}

auto visit2(uint16_t node, std::array<std::array<uint64_t, 3>, 26 * 26 * 26>& visited) {
    if(visited[node][0]) return visited[node];

    auto valid = node == read_compress("dac") || node == read_compress("fft");

    std::array<uint64_t, 3> res{0, 0, 0};
    for(const auto& item : parsed[node]) {
        auto asd = visit2(item, visited);
        if(valid) {
            res[1] += asd[0];
            res[2] += asd[1];
        } else {
            res[0] += asd[0];
            res[1] += asd[1];
            res[2] += asd[2];
        }
    }
    res[0] |= (1ull << 63);
    visited[node] = res;
    return res;
}

uint64_t part2() {
    std::array<std::array<uint64_t, 3>, 26 * 26 * 26> visited{};
    visited[read_compress("out")][0] = 1 | (1ull << 63); // use last bit to indicate value has been set
    return visit2(read_compress("svr"), visited)[2] & ~(1ull << 63);
}

static auto p0 = aoc::test([]() { return (uint64_t)parse().size(); }, 2025, 11, 0, "parse");
static auto p1 = aoc::test(part1, 2025, 11, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 11, 2, "part2");

} // namespace y2025::Day11
