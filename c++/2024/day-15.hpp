#pragma once
#include "../aoc.hpp"
#include "../grid.hpp"

namespace y2024::Day13 {

const auto input = aoc::getInput(2024, 15);

template<int dx, int dy>
bool tryPush1(int x, int y, Grid<50, 50, char>& g) {
    int cx = x + dx;
    int cy = y + dy;

    while(true) { // don't need oob checks
        auto v = g(cx, cy);
        if(v == '#') return false; // can't push
        if(v == '.') break;

        cx += dx;
        cy += dy;
    }
    while(cx != x + dx || cy != y + dy) {
        g(cx, cy) = 'O';
        cx -= dx;
        cy -= dy;
    }
    g(cx, cy) = '.';
    return true;
}

uint64_t part1() {
    Grid<50, 50, char> g;
    int x;
    int y;

    for(int y1 = 0; y1 < 50; y1++) {
        for(int x1 = 0; x1 < 50; x1++) {
            auto v = input[x1 + y1 * 51];
            if(v == '@') {
                x = x1;
                y = y1;
                v = '.';
            }
            g(x1, y1) = v;
        }
    }

    for(int i = 50 * 51 + 1; i < input.size(); i++) {
        char dir = input[i];

        // clang-format off
        if(dir == '>' && tryPush1< 1,  0>(x, y, g)) x++;
        if(dir == '<' && tryPush1<-1,  0>(x, y, g)) x--;
        if(dir == '^' && tryPush1< 0, -1>(x, y, g)) y--;
        if(dir == 'v' && tryPush1< 0,  1>(x, y, g)) y++;
        // clang-format on
    }

    uint64_t result = 0;
    for(int y = 0; y < 50; y++) {
        for(int x = 0; x < 50; x++) {
            if(g(x, y) == 'O')
                result += x + y * 100;
        }
    }
    return result;
}

template<int dx, int dy, bool apply>
bool tryPush2(int x, int y, Grid<100, 50, char>& g) {
    auto curr = g(x, y);
    if(curr == '#') return false;
    if(curr == '.') return true;

    if(dx != 0) { // left/right push
        if(tryPush2<dx, dy, apply>(x + dx + dx, y, g)) {
            if(apply) {
                g(x + dx * 2, y) = g(x + dx, y);
                g(x + dx, y) = curr;
                g(x, y) = '.';
            }
            return true;
        }
    } else { // up/down push
        auto adj = curr == '[' ? 1 : -1;
        if(tryPush2<dx, dy, apply>(x, y + dy, g) && tryPush2<dx, dy, apply>(x + adj, y + dy, g)) {
            if(apply) {
                g(x, y + dy) = g(x, y);
                g(x + adj, y + dy) = g(x + adj, y);

                g(x, y) = '.';
                g(x + adj, y) = '.';
            }
            return true;
        }
    }
    return false;
}

uint64_t part2() {
    Grid<100, 50, char> g;
    int x;
    int y;

    for(int y1 = 0; y1 < 50; y1++) {
        for(int x1 = 0; x1 < 50; x1++) {
            auto v = input[x1 + y1 * 51];
            if(v == 'O') {
                g(x1 * 2, y1) = '[';
                g(x1 * 2 + 1, y1) = ']';
                continue;
            }
            if(v == '@') {
                x = x1 * 2;
                y = y1;
                v = '.';
            }
            g(x1 * 2, y1) = v;
            g(x1 * 2 + 1, y1) = v;
        }
    }

    for(int i = 50 * 51 + 1; i < input.size(); i++) {
        char dir = input[i];

        if(dir == '>' && tryPush2<1, 0, false>(x + 1, y, g)) {
            tryPush2<1, 0, true>(x + 1, y, g);
            x++;
        }
        if(dir == '<' && tryPush2<-1, 0, false>(x - 1, y, g)) {
            tryPush2<-1, 0, true>(x - 1, y, g);
            x--;
        }
        if(dir == '^' && tryPush2<0, -1, false>(x, y - 1, g)) {
            tryPush2<0, -1, true>(x, y - 1, g);
            y--;
        }
        if(dir == 'v' && tryPush2<0, 1, false>(x, y + 1, g)) {
            tryPush2<0, 1, true>(x, y + 1, g);
            y++;
        }
    }

    uint64_t result = 0;
    for(int y = 0; y < 50; y++) {
        for(int x = 0; x < 100; x++) {
            if(g(x, y) == '[')
                result += x + y * 100;
        }
    }
    return result;
}

static auto p1 = aoc::test(part1, 2024, 15, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 15, 2, "part 2");

} // namespace y2024::Day13
