#pragma once
#include <cmath>
#include <print>
#include <unordered_set>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"

namespace y2025::Day8 {

const auto input = aoc::getInput(2025, 8);

auto parse() {
    std::vector<std::tuple<int, int, int>> nums;
    size_t pos = 0;
    while(pos < input.length()) {
        auto a = readUInt(input, pos);
        auto b = readUInt(input, pos);
        auto c = readUInt(input, pos);
        nums.emplace_back(a, b, c);
    }
    return nums;
}

const auto parsed = parse();

auto make_dists() {
    std::vector<std::tuple<int64_t, int, int>> dists;
    dists.reserve((parsed.size() * (parsed.size() - 1)) / 2);

    for(int j = 0; j < parsed.size(); j++) {
        const auto [x1, y1, z1] = parsed[j];

        for(int k = 0; k < j; k++) {
            const auto [x2, y2, z2] = parsed[k];

            int64_t dx = x1 - x2;
            int64_t dy = y1 - y2;
            int64_t dz = z1 - z2;

            auto dist = dx * dx + dy * dy + dz * dz;
            dists.emplace_back(dist, j, k);
        }
    }

    return dists;
}

uint64_t part1() {
    auto dists = make_dists();
    std::partial_sort(dists.begin(), dists.begin() + 1000, dists.end());

    std::vector<std::shared_ptr<std::unordered_set<int>>> groups;

    groups.resize(parsed.size());
    for(int i = 0; i < parsed.size(); i++) {
        groups[i] = std::make_shared<std::unordered_set<int>>();
        groups[i]->insert(i);
    }

    for(int i = 0; i < 1000; i++) {
        auto [d, a, b] = dists[i];

        auto ga = groups[a];
        auto gb = groups[b];
        if(ga == gb) continue;
        for(auto& item : *gb) {
            groups[item] = ga;
        }
        ga->merge(*gb);
    }

    std::unordered_set<std::shared_ptr<std::unordered_set<int>>> sets;
    sets.insert(groups.begin(), groups.end());

    int b1 = 0, b2 = 0, b3 = 0;
    for(auto&& g : sets) {
        auto s = g->size();
        if(s >= b1) {
            b3 = b2;
            b2 = b1;
            b1 = s;
        } else if(s >= b2) {
            b3 = b2;
            b2 = s;
        } else if(s >= b1) {
            b3 = s;
        }
    }

    return b1 * b2 * b3;
}

uint64_t part2() {
    auto dists = make_dists();
    counting_sort(std::span(dists), [](auto& a) { return std::get<0>(a); });

    std::vector<std::shared_ptr<std::unordered_set<int>>> groups;

    groups.resize(parsed.size());
    for(int i = 0; i < parsed.size(); i++) {
        groups[i] = std::make_shared<std::unordered_set<int>>();
        groups[i]->insert(i);
    }

    uint64_t res = 0;
    for(int i = 0; groups[0]->size() < 1000; i++) {
        auto [d, a, b] = dists[i];

        res = (uint64_t)std::get<0>(parsed[a]) * std::get<0>(parsed[b]);

        auto ga = groups[a];
        auto gb = groups[b];
        if(ga == gb) continue;
        for(auto& item : *gb) {
            groups[item] = ga;
        }
        ga->merge(*gb);
    }

    return res;
}

static auto p0 = aoc::test([]() { return (uint64_t)parse().size(); }, 2025, 8, 0, "parse");
static auto p1 = aoc::test(part1, 2025, 8, 1, "part1");
static auto p2 = aoc::test(part2, 2025, 8, 2, "part2");

} // namespace y2025::Day8
