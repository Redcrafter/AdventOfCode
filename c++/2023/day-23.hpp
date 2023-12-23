#pragma once
#include <array>
#include <bitset>

#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"
#include "../vec3.hpp"

namespace y2023::Day23 {

const auto input = readFile("../data/2023/day23.txt");
const auto size = 141;

char get(int x, int y) {
    return input[x + y * (size + 1)];
}

enum Dir {
    Left,
    Right,
    Up,
    Down
};

struct Node;
struct Edge {
    Node* dest = nullptr;
    int length = 0;
    bool valid = false;

    Edge operator+(int v) const {
        return {dest, length + v, valid};
    }
};
struct Node {
    int id = -1;
    std::array<Edge, 4> neighbours{};
};

// object pool to save allocation. could use normal vector for scalability but this barely matters at all
fixedVector<Node, 64> pool;
Grid<size, size, Node*> map;

Edge parse(int x, int y, Dir from, Edge parent) {
    if (x == size - 2 && y == size - 1) {
        pool.push_back({});
        auto n = &pool[pool.size() - 1];
        n->id = pool.size() - 1;
        n->neighbours[from] = parent;
        map(x, y) = n;
        return {n, 0, !parent.valid};
    }

    auto l = get(x - 1, y);
    auto r = get(x + 1, y);
    auto u = get(x, y - 1);
    auto d = get(x, y + 1);

    auto lv = l != '#';
    auto rv = r != '#';
    auto uv = u != '#';
    auto dv = d != '#';

    if (lv + rv + uv + dv < 3) {
        if (from != Left && lv) return parse(x - 1, y, Right, parent + 1) + 1;
        if (from != Right && rv) return parse(x + 1, y, Left, parent + 1) + 1;
        if (from != Up && uv) return parse(x, y - 1, Down, parent + 1) + 1;
        if (from != Down && dv) return parse(x, y + 1, Up, parent + 1) + 1;

#ifdef __GNUC__  // GCC, Clang, ICC
        __builtin_unreachable();
#elif defined(_MSC_VER)  // MSVC
        __assume(false);
#else
        return {};
#endif
    }

    Node* n = map(x, y);
    if (n)
        return {n, 0, !parent.valid};

    pool.push_back({});
    n = &pool[pool.size() - 1];
    n->id = pool.size() - 1;
    n->neighbours[from] = parent;
    map(x, y) = n;

    if (from != Left && lv && !n->neighbours[Left].dest) {
        auto p = parse(x - 1, y, Right, {n, 0, l == '>'});
        n->neighbours[Left] = p;
    }
    if (from != Right && rv && !n->neighbours[Right].dest) {
        auto p = parse(x + 1, y, Left, {n, 0, r == '<'});
        n->neighbours[Right] = p;
    }
    if (from != Up && uv && !n->neighbours[Up].dest) {
        auto p = parse(x, y - 1, Down, {n, 0, u == 'v'});
        n->neighbours[Up] = p;
    }
    if (from != Down && dv && !n->neighbours[Down].dest) {
        auto p = parse(x, y + 1, Up, {n, 0, d == '^'});
        n->neighbours[Down] = p;
    }

    return {n, 0, !parent.valid};
}

template <bool part1>
void search(Node* n, Node* end, std::bitset<64> visited, int dist, int& max) {
    if (n == end) {
        max = std::max(max, dist);
        return;
    }

    visited[n->id] = 1;
    for (auto& o : n->neighbours) {
        if (o.dest && (!part1 || o.valid) && !visited[o.dest->id])
            search<part1>(o.dest, end, visited, dist + o.length + 1, max);
    }
}

template <bool part1>
int solve() {
    map.fill(nullptr);
    pool.clear();

    pool.push_back({});
    auto start = &pool[pool.size() - 1];
    start->id = 0;
    map(1, 0) = start;

    auto asd = parse(1, 1, Up, {start, 0, false});
    start->neighbours[Down] = asd;

    int result = 0;
    search<part1>(start, map(size - 2, size - 1), 0, 0, result);
    return result;
}

uint64_t part1() {
    return solve<true>();
}

uint64_t part2() {
    return solve<false>();
}

}  // namespace y2023::Day23
