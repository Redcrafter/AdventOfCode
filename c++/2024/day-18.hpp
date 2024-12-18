#pragma once
#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2024::Day18 {

const auto input = extractNumbers<uint32_t>(aoc::getInput(2024, 18));
const int width = 71;
const int height = 71;

uint64_t part1() {
    Grid<width, height, bool> visited;
    visited.fill(0);

    for(int i = 0; i < 1024 * 2; i += 2) {
        visited(input[i], input[i + 1]) = true;
    }

    std::vector<std::tuple<uint8_t, uint8_t, uint16_t>> stack;
    stack.reserve(2048);
    stack.push_back({0, 0, 0});

    auto add = [&](int x, int y, int cost) {
        if(x < 0 || y < 0 || x >= width || y >= height)
            return;

        if(!visited(x, y)) {
            visited(x, y) = 1;
            stack.push_back({x, y, cost});
        }
    };

    for(int i = 0; i < stack.size(); i++) {
        auto [x, y, cost] = stack[i];

        if(x == 70 && y == 70)
            return cost;

        add(x - 1, y, cost + 1);
        add(x + 1, y, cost + 1);
        add(x, y - 1, cost + 1);
        add(x, y + 1, cost + 1);
    }

    return 0;
}

template<int dx, int dy>
bool travel(int x, int y, Grid<width, height, bool>& visited) {
    while(true) {
        x += dx;
        y += dy;

        if(x < 0 || x >= width || y < 0 || y >= height) return false;
        if(x == 70 && y == 70) return true;

        if(visited(x, y)) return false;
        visited(x, y) = true;

        if(x - dy >= 0 && x - dy < width && y + dx >= 0 && y + dx < height && !visited(x - dy, y + dx) && travel<-dy, dx>(x, y, visited)) return true;
        if(x + dy >= 0 && x + dy < width && y - dx >= 0 && y - dx < height && !visited(x + dy, y - dx) && travel<dy, -dx>(x, y, visited)) return true;
    }
}

std::string part2() {
    Grid<width, height, bool> visited;

    int l = 1024;
    int r = input.size() / 2 - 1;

    while(l < r) {
        auto m = (l + r) / 2;

        visited.fill(0);
        for(int i = 0; i < m * 2; i += 2) {
            visited(input[i], input[i + 1]) = true;
        }

        if(travel<1, 0>(0, 0, visited) || travel<0, 1>(0, 0, visited)) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return std::to_string(input[l * 2]) + "," + std::to_string(input[l * 2 + 1]);
}

// https://gist.github.com/CameronAavik/94d5978c64eec8fd5cca32ceb8570f61
std::string part2_union() {
    const auto PaddedWidth = width + 2;

    Grid<width + 2, height + 2, uint16_t> parent;
    parent.fill(0xFFFF);
    for(int i = 1; i < width + 1; i++) {
        parent(i, 0) = 0;
        parent(i, height + 1) = 1;
        parent(0, i) = 1;
        parent(width + 1, i) = 0;
    }

    fixedVector<uint16_t, 32> neighbours{};

    int edgeNeighbours = 0;

    auto AddNeighbour = [&](int index) {
        auto value = parent.data[index];
        if(value < 2)
            edgeNeighbours |= 1 << value;
        else if(value != 0xFFFF) {
            neighbours.push_back(index);
            while(value != index) {
                index = value;
                value = parent.data[index];
                if(value < 2) {
                    edgeNeighbours |= 1 << value;
                    break;
                }
                neighbours.push_back(index);
            }
        }
    };

    for(int i = 0; i < input.size(); i += 2) {
        int x = input[i];
        int y = input[i + 1];

        auto index = (x + 1) + (y + 1) * PaddedWidth;

        edgeNeighbours = 0;
        neighbours.clear();

        AddNeighbour(index - PaddedWidth - 1);
        AddNeighbour(index - PaddedWidth);
        AddNeighbour(index - PaddedWidth + 1);
        AddNeighbour(index - 1);
        AddNeighbour(index + 1);
        AddNeighbour(index + PaddedWidth - 1);
        AddNeighbour(index + PaddedWidth);
        AddNeighbour(index + PaddedWidth + 1);

        if(edgeNeighbours == 3) {
            return std::to_string(x) + "," + std::to_string(y);
        }

        auto newRoot = (edgeNeighbours == 0 ? index : edgeNeighbours - 1);
        for(auto neighbour : neighbours)
            parent.data[neighbour] = newRoot;
        parent.data[index] = newRoot;
    }

    return "error";
}

static auto p = aoc::test([]() { return extractNumbers<uint32_t>(aoc::getInput(2024, 18)).size(); }, 2024, 18, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 18, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 18, 2, "part 2");
static auto p2u = aoc::test(part2_union, 2024, 18, 2, "part 2 union");

} // namespace y2024::Day18
