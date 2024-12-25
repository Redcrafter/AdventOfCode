#pragma once
#include <array>
#include <unordered_set>

#include "../aoc.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2022::Day9 {

int praseInt(std::string_view str, int start = 0) {
    int val = 0;
    for(size_t i = start; i < str.size(); i++) {
        auto c = str[i];
        if(c < '0' || c > '9') break;

        val = val * 10 + c - '0';
    }
    return val;
}

int sgn(int val) {
    return (0 < val) - (val < 0);
}

const auto input = split(trimEnd(aoc::getInput(2022, 9)), '\n');

const int arrSize = 520;
uint64_t part1() {
    Grid<arrSize, arrSize, bool> grid{};

    auto hx = arrSize / 2;
    auto hy = arrSize / 2;
    auto tx = arrSize / 2;
    auto ty = arrSize / 2;

    grid(arrSize / 2, arrSize / 2) = 1;
    auto res = 1;

    for(size_t i = 0; i < input.size(); i++) {
        auto a = input[i];
        auto b = praseInt(a, 2);

        auto mx = 0;
        auto my = 0;

        switch(a[0]) {
            case 'L': mx--; break;
            case 'R': mx++; break;
            case 'U': my--; break;
            case 'D': my++; break;
        }

        for(auto j = 0; j < b; j++) {
            hx += mx;
            hy += my;

            auto dx = hx - tx;
            auto dy = hy - ty;

            auto ax = std::abs(dx);
            auto ay = std::abs(dy);

            if((ax >= 1 && ay > 1) || (ax > 1 && ay >= 1)) {
                tx += sgn(dx);
                ty += sgn(dy);
            } else if(ax > 1) {
                tx += sgn(dx);
            } else if(ay > 1) {
                ty += sgn(dy);
            } else {
                continue;
            }

            if(grid(tx, ty) == 0) {
                res++;
                grid(tx, ty) = 1;
            }
        }

        // printf("%i %i\n", tx, ty);
    }

    return res;
}

uint64_t part2() {
    Grid<arrSize, arrSize, bool> grid{};

    std::array<vec2<int>, 10> nodes;
    for(auto i = 0; i < 10; i++) {
        nodes[i] = {arrSize / 2, arrSize / 2};
    }

    grid(arrSize / 2, arrSize / 2) = 1;
    auto res = 1;

    for(size_t i = 0; i < input.size(); i++) {
        auto a = input[i];
        auto b = praseInt(a, 2);

        auto mx = 0;
        auto my = 0;

        switch(a[0]) {
            case 'L': mx--; break;
            case 'R': mx++; break;
            case 'U': my--; break;
            case 'D': my++; break;
        }

        for(auto j = 0; j < b; j++) {
            auto last = &nodes[0];
            last->x += mx;
            last->y += my;

            for(auto k = 1; k < 10; k++) {
                auto n = &nodes[k];

                auto dx = last->x - n->x;
                auto dy = last->y - n->y;

                auto ax = std::abs(dx);
                auto ay = std::abs(dy);

                if((ax >= 1 && ay > 1) || (ax > 1 && ay >= 1)) {
                    n->x += sgn(dx);
                    n->y += sgn(dy);
                } else if(ax > 1) {
                    n->x += sgn(dx);
                } else if(ay > 1) {
                    n->y += sgn(dy);
                } else {
                    goto loop;
                }
                last = n;
            }

            if(grid(nodes[9].x, nodes[9].y) == 0) {
                res++;
                grid(nodes[9].x, nodes[9].y) = 1;
            }
        loop:;
        }
    }

    return res;
}

static auto p1 = aoc::test(part1, 2022, 9, 1, "part1");
static auto p2 = aoc::test(part2, 2022, 9, 2, "part2");

} // namespace y2022::Day9
