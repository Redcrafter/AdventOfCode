#pragma once
#include <array>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day12 {

bool isChar(char c) {
    return 'A' <= c && c <= 'Z';
}

bool isUpperCase(char c) {
    return 'A' <= c && c <= 'Z';
}

auto parseInput() {
    auto input = readLines("../data/2021/day12.txt");

    std::vector<std::pair<std::string, std::string>> data;

    for (auto&& line : input) {
        auto ind = split(line, '-');
        data.emplace_back(ind[0], ind[1]);
    }

    return data;
}

const auto input = parseInput();

std::array<std::vector<int>, 32> buildGraph(const std::vector<std::pair<std::string, std::string>>& input) {
    std::unordered_map<std::string, int> idMap{
        {"start", 0},
        {"end", 1}};
    std::array<std::vector<int>, 32> graph{};

    auto getId = [&](const std::string& n) {
        if (!idMap.contains(n)) {
            int id;
            if (isUpperCase(n[0])) {
                id = idMap.size() + 16;
            } else {
                id = idMap.size();
            }
            idMap[n] = id;
            return id;
        }
        return idMap[n];
    };

    for (auto&& item : input) {
        auto aId = getId(item.first);
        auto bId = getId(item.second);

        if (bId != 0) graph[aId].push_back(bId);
        if (aId != 0) graph[bId].push_back(aId);
    }

    return graph;
}

int part1() {
    auto graph = buildGraph(input);

    std::array<int, 32> visited{0};
    int count = 0;

    std::function<void(int)> scan;
    scan = [&](int current) {
        visited[current] = true;

        for (auto item : graph[current]) {
            if (item == 0) {         // start
            } else if (item == 1) {  // end
                count++;
            } else if (item > 16 || !visited[item]) {
                scan(item);
            }
        }

        visited[current] = false;
    };

    scan(0);
    return count;
}

int part2() {
    auto graph = buildGraph(input);

    std::array<int, 32> visited{0};
    int count = 0;

    std::function<void(int, bool)> scan;
    scan = [&](int current, bool special) {
        visited[current] = true;

        for (auto item : graph[current]) {
            if (item == 0) {         // start
            } else if (item == 1) {  // end
                count++;
            } else if (item > 16 || !visited[item]) {
                scan(item, special);
            } else if (!special) {
                scan(item, true);
                visited[item] = true;
            }
        }

        visited[current] = false;
    };

    scan(0, false);
    return count;
}

}  // namespace Day12
