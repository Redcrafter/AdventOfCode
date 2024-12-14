#pragma once
#include <array>
#include <functional>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2021::Day12 {

bool isUpperCase(char c) {
    return 'A' <= c && c <= 'Z';
}

auto input_ = aoc::getInput(2021, 12);
auto parseInput() {
    std::vector<std::pair<std::string_view, std::string_view>> data;

    for(auto&& line : std::ranges::split_view(input_, '\n')) {
        if(line.empty()) continue;
        auto ind = split(std::string_view(line), '-');
        data.emplace_back(ind[0], ind[1]);
    }

    return data;
}

const auto input = parseInput();

std::array<std::vector<int>, 32> buildGraph() {
    std::unordered_map<std::string_view, int> idMap{
        {"start", 0},
        {"end", 1}};
    std::array<std::vector<int>, 32> graph{};

    auto getId = [&](const std::string_view& n) {
        if(!idMap.contains(n)) {
            int id;
            if(isUpperCase(n[0])) {
                id = idMap.size() + 16;
            } else {
                id = idMap.size();
            }
            idMap[n] = id;
            return id;
        }
        return idMap[n];
    };

    for(auto&& item : input) {
        auto aId = getId(item.first);
        auto bId = getId(item.second);

        if(bId != 0) graph[aId].push_back(bId);
        if(aId != 0) graph[bId].push_back(aId);
    }

    return graph;
}

uint64_t part1() {
    auto graph = buildGraph();

    std::array<int, 32> visited{0};
    int count = 0;

    std::function<void(int)> scan;
    scan = [&](int current) {
        visited[current] = true;

        for(auto item : graph[current]) {
            if(item == 0) {        // start
            } else if(item == 1) { // end
                count++;
            } else if(item > 16 || !visited[item]) {
                scan(item);
            }
        }

        visited[current] = false;
    };

    scan(0);
    return count;
}

uint64_t part2() {
    auto graph = buildGraph();

    std::array<int, 32> visited{0};
    int count = 0;

    std::function<void(int, bool)> scan;
    scan = [&](int current, bool special) {
        visited[current] = true;

        for(auto item : graph[current]) {
            if(item == 0) {        // start
            } else if(item == 1) { // end
                count++;
            } else if(item > 16 || !visited[item]) {
                scan(item, special);
            } else if(!special) {
                scan(item, true);
                visited[item] = true;
            }
        }

        visited[current] = false;
    };

    scan(0, false);
    return count;
}

static auto p1 = aoc::test(part1, 2021, 12, 1, "part1");
static auto p2 = aoc::test(part2, 2021, 12, 2, "part2");

} // namespace y2021::Day12
