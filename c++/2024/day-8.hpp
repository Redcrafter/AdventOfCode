#pragma once
#include <array>
#include <iostream>
#include <vector>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../vec2.hpp"

namespace y2024::Day8 {

const auto input = aoc::getInput(2024, 8);
const int width = 50;
const int height = 50;

auto findGroups() {
    std::array<fixedVector<vec2<uint8_t>, 8>, 'z' - '0' + 1> g{};

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            auto c = input[x + y * (width + 1)];
            if(c != '.') {
                g[c - '0'].push_back(vec2<uint8_t>(x, y));
            }
        }
    }

    return g;
}

uint64_t part1() {
    auto groups = findGroups();

    std::array<uint8_t, width * height> set{};

    auto add = [&](vec2<uint8_t> p) {
        if(p.x >= 0 && p.x < width && p.y >= 0 && p.y < height) {
            set[p.x + p.y * width] = 1;
        }
    };

    for(auto&& g : groups) {
        for(int i = 0; i < g.size(); i++) {
            auto a = g[i];

            for(int j = i + 1; j < g.size(); j++) {
                auto b = g[j];

                auto d = a - b;
                add(a + d);
                add(b - d);
            }
        }
    }

    uint64_t result = 0;
    for(auto&& i : set) {
        result += i;
    }
    return result;
}

uint64_t part2() {
    auto groups = findGroups();

    std::array<uint8_t, width * height> set{};

    for(auto&& g : groups) {
        for(int i = 0; i < g.size(); i++) {
            auto a = vec2<int>(g[i]);

            for(int j = i + 1; j < g.size(); j++) {
                auto b = vec2<int>(g[j]);
                auto d = a - b;

                set[a.x + a.y * width] = 1;
                set[b.x + b.y * width] = 1;

                for(int i = 1;; i++) {
                    auto p = a + d * i;
                    if(p.x < 0 || p.x >= width || p.y < 0 || p.y >= height) break;
                    set[p.x + p.y * width] = 1;
                }
                for(int i = 2;; i++) {
                    auto p = a - d * i;
                    if(p.x < 0 || p.x >= width || p.y < 0 || p.y >= height) break;
                    set[p.x + p.y * width] = 1;
                }
            }
        }
    }

    uint64_t result = 0;
    for(auto&& i : set) {
        result += i;
    }
    return result;
}

static auto p1 = aoc::test(part1, 2024, 8, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 8, 2, "part2");

} // namespace y2024::Day8
