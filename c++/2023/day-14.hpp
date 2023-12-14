#pragma once
#include <array>
#include <unordered_map>

#include "../util.hpp"

namespace y2023::Day14 {

const auto input = readFile("../data/2023/day14.txt");

const int width = 100;
const int height = 100;

void north(Grid<100, 100, uint8_t>& grid) {
    for (int x = 0; x < width; x++) {
        int cached = 0;

        for (int y = height - 1; y >= 0; y--) {
            int c = grid(x, y);
            if (c == 'O') {
                cached++;
                grid(x, y) = '.';
            } else if (c == '#') {
                for (int i = 0; i < cached; i++) {
                    grid(x, y + i + 1) = 'O';
                }
                cached = 0;
            }
        }
        for (int i = 0; i < cached; i++) {
            grid(x, i) = 'O';
        }
    }
}

void south(Grid<100, 100, uint8_t>& grid) {
    for (int x = 0; x < width; x++) {
        int cached = 0;

        for (int y = 0; y < height; y++) {
            int c = grid(x, y);
            if (c == 'O') {
                cached++;
                grid(x, y) = '.';
            } else if (c == '#') {
                for (int i = 0; i < cached; i++) {
                    grid(x, y - i - 1) = 'O';
                }
                cached = 0;
            }
        }
        for (int i = 0; i < cached; i++) {
            grid(x, height - i - 1) = 'O';
        }
    }
}

void west(Grid<100, 100, uint8_t>& grid) {
    for (int y = 0; y < height; y++) {
        int cached = 0;

        for (int x = width - 1; x >= 0; x--) {
            int c = grid(x, y);
            if (c == 'O') {
                cached++;
                grid(x, y) = '.';
            } else if (c == '#') {
                for (int i = 0; i < cached; i++) {
                    grid(x + i + 1, y) = 'O';
                }
                cached = 0;
            }
        }
        for (int i = 0; i < cached; i++) {
            grid(i, y) = 'O';
        }
    }
}

void east(Grid<100, 100, uint8_t>& grid) {
    for (int y = 0; y < height; y++) {
        int cached = 0;

        for (int x = 0; x < width; x++) {
            int c = grid(x, y);
            if (c == 'O') {
                cached++;
                grid(x, y) = '.';
            } else if (c == '#') {
                for (int i = 0; i < cached; i++) {
                    grid(x - i - 1, y) = 'O';
                }
                cached = 0;
            }
        }
        for (int i = 0; i < cached; i++) {
            grid(width - i - 1, y) = 'O';
        }
    }
}

uint32_t hash(Grid<100, 100, uint8_t>& grid) {
    uint32_t hash;
    for (size_t i = 0; i < grid.data.size(); i++) {
        if (grid.data[i] == 'O') {
            hash = hash * 31 + i;
        }
    }
    return hash;
}

uint64_t part1() {
    uint64_t result = 0;

    for (int x = 0; x < width; x++) {
        int cached = 0;
        for (int y = height - 1; y >= 0; y--) {
            auto c = input[x + y * 101];
            if (c == 'O') {
                cached++;
            } else if (c == '#') {
                result += -(cached * (cached + 2 * y - 199)) / 2;
                cached = 0;
            }
        }
        result += -(cached * (cached - 201)) / 2;
    }

    return result;
}

uint64_t part2() {
    Grid<100, 100, uint8_t> grid;

    size_t pos = 0;
    for (size_t y = 0; y < 100; y++) {
        for (size_t x = 0; x < 100; x++) {
            grid(x, y) = input[pos++];
        }
        pos++;
    }

    std::unordered_map<uint32_t, int> map;
    for (int i = 0; i < 1000000000; i++) {
        north(grid);
        west(grid);
        south(grid);
        east(grid);

        auto c = hash(grid);
        if (map.contains(c)) {
            i = 1000000000 - (1000000000 - i) % (i - map[c]);
        }
        map[c] = i;
    }

    uint64_t result = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid(x, y) == 'O') {
                result += height - y;
            }
        }
    }
    return result;
}

}  // namespace y2023::Day14
