#pragma once
#include <array>
#include <unordered_set>

#include "../util.hpp"

namespace y2024::Day12 {

const auto input = readFile("../data/2024/day12.txt");

const int width = 140;
const int height = 140;
const int width1 = width + 1;

using arr = std::array<uint8_t, width * height>;

uint32_t rec1(int x, int y, char c, arr& inner, arr& visited) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return 1 << 16;
    }
    if (inner[x + y * width]) return 0;

    if (input[x + y * width1] == c) {
        inner[x + y * width] = 1;
        visited[x + y * width] = 1;

        return rec1(x - 1, y, c, inner, visited) +
               rec1(x, y + 1, c, inner, visited) +
               rec1(x, y - 1, c, inner, visited) +
               rec1(x + 1, y, c, inner, visited) + 1;
    }
    return 1 << 16;
}

uint64_t part1() {
    uint64_t result = 0;

    arr visited{};
    arr inner{};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (visited[x + y * width]) continue;
            auto c = input[x + y * width1];

            inner.fill(0);
            auto outer = rec1(x, y, c, inner, visited);

            result += (outer & 0xFFFF) * (outer >> 16);
        }
    }

    return result;
}

uint32_t rec2(int x, int y, char c, arr& inner, arr& visited, std::unordered_set<uint64_t>& edges) {
    if (x < 0 || x >= width || y < 0 || y >= height) return 0;
    if (inner[x + y * width]) return 0;

    if (input[x + y * width1] == c) {
        inner[x + y * width] = 1;
        visited[x + y * width] = 1;

        if (x == 0 || input[(x - 1) + y * width1] != c) {  // left
            edges.insert(((x + y * width) << 2) | 0);
        }
        if (x + 1 == width || input[(x + 1) + y * width1] != c) {  // right
            edges.insert(((x + y * width) << 2) | 1);
        }
        if (y == 0 || input[x + (y - 1) * width1] != c) {
            edges.insert(((x + y * width) << 2) | 2);  // top
        }
        if (y + 1 == height || input[x + (y + 1) * width1] != c) {
            edges.insert(((x + y * width) << 2) | 3);  // bottom
        }

        return rec2(x - 1, y, c, inner, visited, edges) +
               rec2(x, y + 1, c, inner, visited, edges) +
               rec2(x, y - 1, c, inner, visited, edges) +
               rec2(x + 1, y, c, inner, visited, edges) + 1;
    } else {
        inner[x + y * width] = 1;
    }
    return 0;
}

uint64_t part2() {
    uint64_t result = 0;

    arr visited{};
    arr inner{};
    std::unordered_set<uint64_t> edges;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (visited[x + y * width]) continue;
            auto c = input[x + y * width1];

            inner.fill(0);
            edges.clear();
            auto area = rec2(x, y, c, inner, visited, edges);

            auto corners = 0;
            for (auto el : edges) {
                auto dir = el & 3;
                auto y = ((el >> 2) / width) | 0;
                auto x = (el >> 2) % width;

                if (dir == 2 && !edges.contains(((x + 1 + y * width) << 2) | 2))
                    corners++;
                if (dir == 3 && !edges.contains(((x + 1 + y * width) << 2) | 3))
                    corners++;
                if (dir == 0 && !edges.contains(((x + (y + 1) * width) << 2) | 0))
                    corners++;
                if (dir == 1 && !edges.contains(((x + (y + 1) * width) << 2) | 1))
                    corners++;
            }

            result += area * corners;
        }
    }

    return result;
}

}  // namespace y2024::Day12
