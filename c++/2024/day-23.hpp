#pragma once
#include <unordered_map>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../flatSet.hpp"

namespace y2024::Day23 {

auto parse() {
    const auto input = aoc::getInput(2024, 23);

    std::unordered_map<uint16_t, fixedVector<uint16_t, 13>> map;
    for(size_t i = 0; i < input.size(); i += 6) {
        auto a = (input[i] << 8) | input[i + 1];
        auto b = (input[i + 3] << 8) | input[i + 4];

        map[a].push_back(b);
        map[b].push_back(a);
    }
    return map;
}
const auto map = parse();

uint64_t part1() {
    FlatSet<uint64_t, 2000> groups;

    for(auto& [a, val] : map) {
        if((a >> 8) != 't') continue;

        for(auto b : val) {
            for(auto c : map.at(b)) {
                if(val.contains(c)) {

                    uint16_t a1 = a, b1 = b, c1 = c;
                    if(c1 < b1) std::swap(c1, b1);
                    if(b1 < a1) std::swap(b1, a1);
                    if(c1 < b1) std::swap(c1, b1);

                    groups.insert(a1 | (b1 << 16) | (((uint64_t)c1) << 32));
                }
            }
        }
    }

    return groups.size();
}

void findGroup(uint16_t a, fixedVector<uint16_t, 16>& set, fixedVector<uint16_t, 16>& best, FlatSet<uint16_t, 32>& checked) {
    if(checked.contains(a)) return;

    auto valid = true;
    auto sub = map.at(a);
    for(auto el : set) {
        if(!sub.contains(el)) {
            valid = false;
            break;
        }
    }
    if(!valid) return;

    set.push_back(a);
    if(set.size() > best.size()) {
        best = set;
    }
    for(auto el : sub) {
        if(!set.contains(el)) {
            findGroup(el, set, best, checked);
        }
    }
    set.pop_back();

    checked.insert(a);
}

std::string toResult(std::vector<uint16_t>& arr) {
    std::ranges::sort(arr);

    std::string res;
    res.reserve(arr.size() * 3 - 1);
    for(size_t i = 0; i < arr.size(); i++) {
        auto v = arr[i];
        if(i > 0) res += ',';
        res += v >> 8;
        res += v & 0xFF;
    }
    return res;
}

std::string part2() {
    fixedVector<uint16_t, 16> set, best;
    FlatSet<uint16_t, 32> checked;

    for(auto& [a, val] : map) {
        checked.clear();
        findGroup(a, set, best, checked);
    }

    std::vector<uint16_t> res;
    res.reserve(best.size());
    for(auto v : best) {
        res.push_back(v);
    }

    return toResult(res);
}

std::string part2_fast() {
    FlatSet<int16_t, 256> uniqueNodes;
    std::vector<uint16_t> others;
    std::vector<const fixedVector<uint16_t, 13>*> networks(14);

    for(auto& [a, connected] : map) {
        uniqueNodes.clear();
        others.clear();
        networks.clear();

        networks.push_back(&connected);

        for(auto node : connected) {
            auto& net = map.at(node);
            networks.push_back(&net);
            for(auto n : net) {
                uniqueNodes.insert(n);
            }
            uniqueNodes.insert(node);
        }

        auto self = connected.size() + 1;

        for(auto u : uniqueNodes.data) {
            if(u == uniqueNodes.empty) continue;

            if(u == a) continue;
            int n = 1;
            for(auto& net : networks) {
                n += net->contains(u);
            }
            if(n == self - 1) {
                others.push_back(u);
            }
        }

        if(others.size() == self - 2) {
            others.push_back(a);
            return toResult(others);
        }
    }
    return "";
}

static auto p = aoc::test([]() { return parse().size(); }, 2024, 23, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 23, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 23, 2, "part 2");
static auto p2f = aoc::test(part2_fast, 2024, 23, 2, "part 2 cheese");

} // namespace y2024::Day23
