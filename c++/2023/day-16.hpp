#pragma once
#include <array>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "../grid.hpp"
#include "../util.hpp"

namespace y2023::Day16 {

const auto input = readFile("../data/2023/day16.txt");

const int width = 110;
const int height = 110;

using pt = vec2<int8_t>;
using bt = std::bitset<width * height>;
using loopinfo = std::unordered_map<int, std::unordered_set<int>>;

Grid<width, height, uint8_t> visited;
Grid<width, height, std::array<pt, 4>> precalc;
std::unordered_map<int, bt> cache;

void cast(int x, int y, int dx, int dy) {
    auto dir = 1 << (dx + (dy << 1) + 2);
    while (x >= 0 && x < width && y >= 0 && y < height) {
        auto& t = visited(x, y);
        if ((t & dir) != 0)
            return;
        t |= dir;

        auto c = input[x + y * 111];
        if (c == '|' && dx != 0) {
            cast(x, y - 1, 0, -1);
            cast(x, y + 1, 0, 1);
            break;
        } else if (c == '-' && dy != 0) {
            cast(x - 1, y, -1, 0);
            cast(x + 1, y, 1, 0);
            break;
        } else if (c == '/') {
            std::tie(dx, dy) = std::tuple(-dy, -dx);
            dir = 1 << (dx + (dy << 1) + 2);
        } else if (c == '\\') {
            std::tie(dx, dy) = std::tuple(dy, dx);
            dir = 1 << (dx + (dy << 1) + 2);
        }
        x += dx;
        y += dy;
    }
}

uint64_t countVisited() {
    uint64_t result = 0;
    for (auto i : visited.data) {
        result += (i != 0);
    }
    return result;
}

uint64_t castNormal(int x, int y, int dx, int dy) {
    visited.fill(0);
    cast(x, y, dx, dy);
    return countVisited();
}

uint64_t part1() {
    return castNormal(0, 0, 1, 0);
}

uint64_t part2() {
    uint64_t result = 0;
    for (int x = 0; x < width; x++) {
        result = std::max(result, castNormal(x, 0, 0, 1));
        result = std::max(result, castNormal(x, (height - 1), 0, -1));
    }
    for (int y = 0; y < height; y++) {
        result = std::max(result, castNormal(0, y, 1, 0));
        result = std::max(result, castNormal(width - 1, y, -1, 0));
    }
    return result;
}

enum Dir {
    Left,
    Right,
    Up,
    Down
};

Dir invDir(Dir d) {
    if (d == Dir::Left) return Dir::Right;
    if (d == Dir::Right) return Dir::Left;
    if (d == Dir::Up) return Dir::Down;
    if (d == Dir::Down) return Dir::Up;
    return Dir::Left;
}

void trace(pt start, Dir d) {
    if (precalc(start)[d] != 0)
        return;

    pt delta;
    if (d == Dir::Left) delta = {-1, 0};
    if (d == Dir::Right) delta = {1, 0};
    if (d == Dir::Up) delta = {0, -1};
    if (d == Dir::Down) delta = {0, 1};

    auto pos = start;
    pos += delta;
    while (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
        char c = input[pos.x + pos.y * 111];
        if (!(c == '.' || (c == '|' && (d == Down || d == Up)) || (c == '-' && (d == Left || d == Right)))) {
            break;
        }
        pos += delta;
    }

    precalc(start)[d] = pos;
    // if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height)
    //     precalc(pos)[invDir(d)] = start;
};

void shit(pt pos, Dir dir);

void followPrecalc(pt pos, Dir dir) {
    auto next = precalc(pos)[dir];
    auto delta = (next - pos).sign();
    auto v = 1 << (delta.x + (delta.y << 1) + 2);

    if (pos.x < next.x) {
        pos.x++;
        if ((visited(pos) & v) != 0) return;
        while (pos.x != next.x) {
            visited(pos) |= v;
            pos.x++;
        }
    } else if (pos.x > next.x) {
        pos.x--;
        if ((visited(pos) & v) != 0) return;
        while (pos.x != next.x) {
            visited(pos) |= v;
            pos.x--;
        }
    } else if (pos.y < next.y) {
        pos.y++;
        if ((visited(pos) & v) != 0) return;
        auto i = pos.x + pos.y * width;  // have to help out a bit to vectorize it correclty
        while (pos.y != next.y) {
            visited.data[i] |= v;
            pos.y++;
            i += width;
        }
    } else {
        pos.y--;
        if ((visited(pos) & v) != 0) return;
        auto i = pos.x + pos.y * width;  // have to help out a bit to vectorize it correclty
        while (pos.y != next.y) {
            visited.data[i] |= v;
            pos.y--;
            i -= width;
        }
    }

    if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
        return;

    if ((visited(pos) & v) != 0) {
        return;
    }
    visited(pos) |= v;

    shit(pos, dir);
}

void shit(pt pos, Dir dir) {
    char c = input[pos.x + pos.y * 111];
    if (c == '|') {
        followPrecalc(pos, Dir::Up);
        followPrecalc(pos, Dir::Down);
    } else if (c == '-') {
        followPrecalc(pos, Dir::Left);
        followPrecalc(pos, Dir::Right);
    } else if (c == '/') {
        switch (dir) {
            case Dir::Left:
                followPrecalc(pos, Dir::Down);
                break;
            case Dir::Right:
                followPrecalc(pos, Dir::Up);
                break;
            case Dir::Up:
                followPrecalc(pos, Dir::Right);
                break;
            case Dir::Down:
                followPrecalc(pos, Dir::Left);
                break;
        }
    } else if (c == '\\') {
        switch (dir) {
            case Dir::Left:
                followPrecalc(pos, Dir::Up);
                break;
            case Dir::Right:
                followPrecalc(pos, Dir::Down);
                break;
            case Dir::Up:
                followPrecalc(pos, Dir::Left);
                break;
            case Dir::Down:
                followPrecalc(pos, Dir::Right);
                break;
        }
    } else {
    }
}

uint64_t cast2(pt pos, pt delta) {
    visited.fill(0);

    auto dir = 1 << (delta.x + (delta.y << 1) + 2);

    Dir d;
    if (delta.x == 1) d = Dir::Right;
    if (delta.x == -1) d = Dir::Left;
    if (delta.y == 1) d = Dir::Down;
    if (delta.y == -1) d = Dir::Up;

    // find initial symbol
    while (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
        visited(pos) |= dir;
        char c = input[pos.x + pos.y * 111];
        if (!(c == '.' || (c == '|' && (d == Down || d == Up)) || (c == '-' && (d == Left || d == Right)))) {
            break;
        }
        pos += delta;
    }

    shit(pos, d);
    return countVisited();
}

uint64_t part2_precalc() {
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto c = input[x + y * 111];

            pt p(x, y);
            if (c == '|') {
                trace(p, Dir::Up);
                trace(p, Dir::Down);
            } else if (c == '-') {
                trace(p, Dir::Left);
                trace(p, Dir::Right);
            } else if (c == '/' || c == '\\') {
                trace(p, Dir::Up);
                trace(p, Dir::Down);
                trace(p, Dir::Left);
                trace(p, Dir::Right);
            }
        }
    }

    uint64_t result = 0;
    for (int x = 0; x < width; x++) {
        result = std::max(result, cast2({(int8_t)x, 0}, {0, 1}));
        result = std::max(result, cast2({(int8_t)x, (int8_t)(height - 1)}, {0, -1}));
    }
    for (int y = 0; y < height; y++) {
        result = std::max(result, cast2({0, (int8_t)y}, {1, 0}));
        result = std::max(result, cast2({(int8_t)(width - 1), (int8_t)y}, {-1, 0}));
    }
    return result;
}

pt findMirror(bt& set, int x, int y, int dx, int dy) {
    while (x >= 0 && x < width && y >= 0 && y < height) {
        set.set(x + y * width, true);

        auto c = input[x + y * 111];
        if (c == '|' && dx != 0) {
            return pt(x, y);
        } else if (c == '-' && dy != 0) {
            return pt(x, y);
        } else if (c == '/') {
            std::tie(dx, dy) = std::tuple(-dy, -dx);
        } else if (c == '\\') {
            std::tie(dx, dy) = std::tuple(dy, dx);
        }
        x += dx;
        y += dy;
    }
    return pt(-1);
}

std::tuple<bt*, std::shared_ptr<loopinfo>> builtSet(int x, int y, std::unordered_set<int>& seen) {
    int i = x + y * width;

    if (seen.contains(i)) {
        auto shit = std::make_shared<loopinfo>();
        (*shit)[i] = {};
        return {nullptr, shit};
    }
    if (cache.contains(i))
        return {&cache[i], nullptr};

    seen.emplace(i);

    bt& set = cache[i];
    set.reset();

    pt a, b;
    auto c = input[x + y * 111];
    if (c == '|') {
        a = findMirror(set, x, y, 0, -1);
        b = findMirror(set, x, y, 0, 1);
    } else {
        a = findMirror(set, x, y, -1, 0);
        b = findMirror(set, x, y, 1, 0);
    }

    std::shared_ptr<loopinfo> al, bl, asd;
    if (a != -1) {
        auto [bit, l] = builtSet(a.x, a.y, seen);
        if (bit)
            set |= *bit;
        al = l;
    }
    if (b != -1) {
        auto [bit, l] = builtSet(b.x, b.y, seen);
        if (bit)
            set |= *bit;
        bl = l;
    }

    if (al && bl) {
        for (auto& [key, val] : *bl) {
            if (al->contains(key)) {
                auto& arr = (*al)[key];
                for (auto ind : val) {
                    arr.emplace(ind);
                }
            } else {
                (*al)[key] = val;
            }
        }
        asd = al;
    } else if (al) {
        asd = al;
    } else if (bl) {
        asd = bl;
    }

    if (asd) {
        // If the current mirror was the start of a cycle, then remove it from the cycle dictionary and set all the
        // mirrors in the cycle to have the same seenBits as the current mirror as they should all have the same value
        if (asd->contains(i)) {
            auto& cycleIndexes = (*asd)[i];
            for (auto ind : cycleIndexes) {
                cache[ind] = set;
            }
            asd->erase(i);
        }

        if (asd->size() == 0) {
            asd = nullptr;
        } else {
            // Insert the current mirror index into all the current cycles
            for (auto& [_, cycleIndexSet] : *asd) {
                cycleIndexSet.emplace(i);
            }
        }
    }

    seen.erase(i);
    return {&set, asd};
}

uint64_t part2_bits() {
    cache.clear();

    std::unordered_set<int> seen;

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            auto c = input[x + y * 111];

            if (c == '|' || c == '-') {
                seen.clear();
                builtSet(x, y, seen);
            }
        }
    }

    bt bits;
    auto cast3 = [&](int x, int y, int dx, int dy) {
        bits.reset();
        auto pos = findMirror(bits, x, y, dx, dy);
        bits |= cache[pos.x + pos.y * width];
        return bits.count();
    };

    uint64_t result = 0;
    for (int x = 0; x < width; x++) {
        result = std::max(result, cast3(x, 0, 0, 1));
        result = std::max(result, cast3(x, height - 1, 0, -1));
    }
    for (int y = 0; y < height; y++) {
        result = std::max(result, cast3(0, y, 1, 0));
        result = std::max(result, cast3(width - 1, y, -1, 0));
    }
    return result;
}

}  // namespace y2023::Day16
