#pragma once
#include <array>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day6 {

const auto input = aoc::getInput(2024, 6);

constexpr int width = 130;
constexpr int height = 130;

constexpr int width1 = width + 1; // actual string length

std::pair<int, int> findStart() {
    for(int i = 0; i < input.size(); i++) {
        if(input[i] == '^') return {i % width1, i / width1};
    }
    return {0, 0};
}

template<int dx, int dy>
auto line(std::array<uint8_t, width * height>& s, int& x, int& y) {
    while(true) {
        auto nx = x + dx;
        auto ny = y + dy;
        if(nx < 0 || nx == width || ny < 0 || ny == height) {
            return true;
        }

        if(input[nx + ny * width1] == '#') return false;
        x = nx;
        y = ny;
        s[x + y * width] = 1;
    }
}

auto base_path() {
    // auto [x, y] = findStart();
    int x = 61;
    int y = 85;

    std::array<uint8_t, width * height> s{};
    s[x + y * width] = 1;

    while(true) {
        if(line<0, -1>(s, x, y)) return s;
        if(line<1, 0>(s, x, y)) return s;
        if(line<0, 1>(s, x, y)) return s;
        if(line<-1, 0>(s, x, y)) return s;
    }
}

uint64_t part1() {
    uint64_t result = 0;
    for(auto i : base_path())
        result += i;
    return result;
}

auto base_path_cache() {
    int x = 61;
    int y = 85;

    std::array<uint16_t, width * height> move_cache{};
    std::array<uint8_t, width * height> s{};

    s[x + y * width] = 1;

    int lastX = x;
    int lastY = y;

    while(true) {
        // dy = -1
        while(true) {
            if(y == 0) {
                move_cache[lastX + lastY * width] = -1;
                return std::pair(s, move_cache);
            }
            if(input[x + (y - 1) * width1] == 35) break;

            y--;
            s[x + y * width] = 1;
        }
        if(y != lastY) move_cache[lastX + lastY * width] = x | (y << 8);
        lastY = y;

        // dx = 1
        while(true) {
            if(x + 1 == width) {
                move_cache[lastX + lastY * width] = (x + 1) | (y << 8);
                return std::pair(s, move_cache);
            }
            if(input[x + 1 + y * width1] == 35) break;

            x++;
            s[x + y * width] = 1;
        }
        if(x != lastX) move_cache[lastX + lastY * width] = x | (y << 8);
        lastX = x;

        // dy = 1
        while(true) {
            if(y + 1 == height) {
                move_cache[lastX + lastY * width] = x | ((y + 1) << 8);
                return std::pair(s, move_cache);
            }
            if(input[x + (y + 1) * width1] == 35) break;

            y++;
            s[x + y * width] = 1;
        }
        if(y != lastY) move_cache[lastX + lastY * width] = x | (y << 8);
        lastY = y;

        // dx = -1
        while(true) {
            if(x - 1 < 0) {
                move_cache[lastX + lastY * width] = -1;
                return std::pair(s, move_cache);
            }
            if(input[x - 1 + y * width1] == 35) break;

            x--;
            s[x + y * width] = 1;
        }
        if(x != lastX) move_cache[lastX + lastY * width] = x | (y << 8);
        lastX = x;
    }
}

template<typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

auto testRoute(std::array<uint8_t, width * height>& s, std::array<uint16_t, width * height>& move_cache, int wx, int wy, int x, int y, int dx, int dy) {
    while(true) {
        auto c = move_cache[x + y * width];

        auto lastX = x;
        auto lastY = y;
        auto doCache = true;
        auto doStep = true;

        if(c != 0xFFFF && c != 0) {
            doStep = false;
            auto nx = (c & 0xFF);
            auto ny = (c >> 8);

            dx = sgn(nx - x);
            dy = sgn(ny - y);

            if((nx == x && nx == wx && ((y < wy && wy <= ny) || (ny <= wy && wy < y))) || (ny == y && ny == wy && ((x < wx && wx <= nx) || (nx <= wx && wx < x)))) {
                x = wx - dx;
                y = wy - dy;
                doCache = false; // hit wall so don't do cache
                doStep = true;

                s[x + y * width] = 1;
            } else {
                if(nx == width || ny == height) return false;

                x = nx;
                y = ny;
            }
        }

        if(doStep) {
            std::tie(dx, dy) = std::make_tuple(-dy, dx);
            while(input[(x + dx) + (y + dy) * width1] == 35 || ((x + dx) == wx && (y + dy) == wy)) {
                if(((x + dx) == wx && (y + dy) == wy)) doCache = false;
                std::tie(dx, dy) = std::make_tuple(-dy, dx);
            }

            while(true) {
                auto nx = x + dx;
                auto ny = y + dy;

                if(!(nx >= 0 && nx < width && ny >= 0 && ny < height)) {
                    // move_cache[x + y * width] = -1;
                    return false;
                }
                if(nx == wx && ny == wy) {
                    doCache = false; // hit wall so don't do cache
                    break;
                } else if(input[nx + ny * width1] == 35) {
                    break;
                } else {
                    x = nx;
                    y = ny;
                }
            }
        }

        if(doCache) {
            move_cache[lastX + lastY * width] = x | (y << 8);
        }

        if(s[x + y * width] == 1) {
            return true;
        }
        s[x + y * width] = 1;
    }
}

uint64_t part2() {
    auto [s, move_cache] = base_path_cache();
    uint64_t result = 0;

    std::array<uint8_t, width * height> visited{};
    std::array<uint8_t, width * height> pre_cache{};  // collisions visited by this function
    std::array<uint8_t, width * height> post_cache{}; // collisions visited by testRoute

    int x = 61;
    int y = 85;

    while(true) {
        auto c = move_cache[x + y * width];
        if(c == 0xFFFF) return result;
        auto nx = (c & 0xFF);
        auto ny = (c >> 8);

        auto dx = sgn(nx - x);
        auto dy = sgn(ny - y);

        while(x != nx || y != ny) {
            auto wx = x + dx;
            auto wy = y + dy;

            if(wx == width || wy == height) return result;

            if(visited[wx + wy * width] == 0) {
                post_cache = pre_cache;

                auto t = move_cache[x + y * width];
                move_cache[x + y * width] = 0;
                result += testRoute(post_cache, move_cache, wx, wy, x, y, dx, dy);
                move_cache[x + y * width] = t;
            }

            visited[wx + wy * width] = 1;
            x = wx;
            y = wy;
        }
        pre_cache[x + y * width] = 1;
    }
}

static auto p1 = aoc::test(part1, 2024, 6, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 6, 2, "part2");

} // namespace y2024::Day6
