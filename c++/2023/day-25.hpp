#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <queue>
#include <random>

#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2023::Day25 {

const auto input = readFile("../data/2023/day25.txt");

struct El {
    El* parent;
    int size = 0;
};

fixedVector<El, 2400> pool;  // probably big enough
std::array<int, 0x1F1F1F> labelMap;
int groupCount = 0;

El* find(El* x) {
    while (x->parent != x) {
        auto t = x->parent;
        x->parent = x->parent->parent;
        x = t;
    }
    return x;
}
void merge(El* a, El* b) {
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (a->size < b->size) {
        std::swap(a, b);
    }

    b->parent = a;
    a->size += b->size;
    groupCount--;
}

uint64_t part1() {
    std::vector<std::tuple<El*, El*>> edges;
    edges.reserve(1200);
    pool.clear();
    labelMap.fill(-1);

    size_t pos = 0;
    while (pos < input.size()) {
        auto label = *(uint32_t*)(input.data() + pos) & 0x1F1F1F;
        pos += 5;

        int id = labelMap[label];
        if (id == -1) {
            id = pool.size();
            pool.push_back({});
            labelMap[label] = id;
        }

        while (true) {
            auto other = *(uint32_t*)(input.data() + pos);
            pos += 4;

            auto l1 = other & 0x1F1F1F;
            int id1 = labelMap[l1];
            if (id1 == -1) {
                id1 = pool.size();
                pool.push_back({});
                labelMap[l1] = id1;
            }

            edges.emplace_back(&pool[id], &pool[id1]);

            if ((other >> 24) == '\n') {
                break;
            }
        }
    }

    std::random_device rd;
    std::default_random_engine rnd(rd());

    while (true) {
        std::shuffle(edges.begin(), edges.end(), rnd);

        for (size_t i = 0; i < pool.size(); i++) {
            auto el = &pool[i];
            el->parent = el;
            el->size = 1;
        }
        groupCount = pool.size();

        int i = 0;
        for (; groupCount > 2; i++) {
            auto [a, b] = edges[i];
            merge(a, b);
        }

        auto count = 0;
        auto val = 0;
        for (; i < edges.size() && count <= 3; i++) {
            auto [a, b] = edges[i];

            auto a1 = find(a);
            auto b1 = find(b);
            if (a1 != b1) {
                val = a1->size * b1->size;
                count++;
            }
        }

        if (count == 3) {
            return val;
        }
    }
    return 0;
}

}  // namespace y2023::Day25
