#pragma once
#include <array>
#include <cstdint>

namespace Day20 {

uint64_t part2() {
    auto input = readLines("../data/2021/day20.txt");

    const int pad = 55;
    const int width = 100 + pad * 2;
    const int height = 100 + pad * 2;

    std::array<uint8_t, 512> map;
    for (int i = 0; i < 512; i++) map[i] = input[0][i] == '#';

    std::array<uint8_t, width * height> grid;
    std::array<uint8_t, width * height> next;

    std::fill(grid.begin(), grid.end(), 0);
    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            grid[(x + 55) + (y + 55) * width] = input[y + 1][x] == '#';
        }
    }

    for (int i = 0; i < 25; i++) {
        #pragma clang loop unroll(full)
        for (int i = width + 1; i < grid.size() - width - 1; i++) {
            int num =
                grid[i - width - 1] << 8 | grid[i - width] << 7 | grid[i - width + 1] << 6 |
                grid[i         - 1] << 5 | grid[i        ] << 4 | grid[i         + 1] << 3 |
                grid[i + width - 1] << 2 | grid[i + width] << 1 | grid[i + width + 1] << 0;

            next[i] = map[num];
        }

        // fill in edges
        int inf = next[width + 1];
        for (int i = 0; i < width; i++) {
            next[i] = inf;
            next[i + (height - 1) * width] = inf;

            next[i * width] = inf;
            next[i * width + (width - 1)] = inf;
        }
        


        #pragma clang loop unroll(full)
        for (int i = width + 1; i < next.size() - width - 1; i++) {
            int num =
                next[i - width - 1] << 8 | next[i - width] << 7 | next[i - width + 1] << 6 |
                next[i         - 1] << 5 | next[i        ] << 4 | next[i         + 1] << 3 |
                next[i + width - 1] << 2 | next[i + width] << 1 | next[i + width + 1] << 0;

            grid[i] = map[num];
        }

        // fill in edges
        inf = grid[width + 1];
        for (int i = 0; i < width; i++) {
            grid[i] = inf;
            grid[i + (height - 1) * width] = inf;

            grid[i * width] = inf;
            grid[i * width + (width - 1)] = inf;
        }
    }

    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        count += grid[i];
    }
    return count;
}

}  // namespace Day20
