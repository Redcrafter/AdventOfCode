#pragma once
#include <algorithm>
#include <bitset>
#include <tuple>
#include <vector>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../grid.hpp"
#include "../util.hpp"
#include "../vec3.hpp"

namespace y2023::Day22 {

const auto input = aoc::getInput(2023, 22);

struct Object {
    vec3<int> start;
    vec3<int> end;

    fixedVector<int, 10> above;
    fixedVector<int, 10> below;

    void addS(int val) {
        for(auto i : above) {
            if(val == i) return;
        }
        above.push_back(val);
    }
    void addD(int val) {
        for(auto i : below) {
            if(val == i) return;
        }
        below.push_back(val);
    }
};

vec3<int> readVec(size_t& pos) {
    auto x = input[pos] & 0xF;
    auto y = input[pos + 2] & 0xF;
    pos += 4;
    auto z = readUInt(input, pos) - 1;

    return vec3<int>(x, y, z);
}

std::vector<Object> objects;

always__inline void parse() {
    Grid<10, 10, std::tuple<int, int>> heights;
    heights.fill({-1, 0});
    objects.clear();

    size_t pos = 0;
    while(pos < input.size()) {
        auto a = readVec(pos);
        auto b = readVec(pos);
        objects.emplace_back(a, b);
    }

    std::sort(objects.begin(), objects.end(), [](auto& a, auto& b) { return a.start.z < b.start.z; });

    for(size_t i = 0; i < objects.size(); i++) {
        auto& obj = objects[i];

        if(obj.start.x != obj.end.x) {
            auto z = 0;
            for(int i = obj.start.x; i <= obj.end.x; i++) {
                z = std::max(z, std::get<1>(heights(i, obj.start.y)));
            }

            obj.end.z = (obj.end.z - obj.start.z) + z;
            obj.start.z = z;

            for(int j = obj.start.x; j <= obj.end.x; j++) {
                auto [c, d] = (heights(j, obj.start.y));
                if(c != -1 && d == z) {
                    obj.addD(c);
                    objects[c].addS(i);
                }
                heights(j, obj.start.y) = {i, z + 1};
            }
        } else if(obj.start.y != obj.end.y) {
            auto z = 0;
            for(int i = obj.start.y; i <= obj.end.y; i++) {
                z = std::max(z, std::get<1>(heights(obj.start.x, i)));
            }

            obj.end.z = (obj.end.z - obj.start.z) + z;
            obj.start.z = z;

            for(int j = obj.start.y; j <= obj.end.y; j++) {
                auto [c, d] = (heights(obj.start.x, j));
                if(c != -1 && d == z) {
                    obj.addD(c);
                    objects[c].addS(i);
                }
                heights(obj.start.x, j) = {i, z + 1};
            }
        } else {
            // find maximum viable z position
            auto [c, z] = heights(obj.start.x, obj.start.y);

            obj.end.z = (obj.end.z - obj.start.z) + z;
            obj.start.z = z;
            if(c != -1) {
                obj.addD(c);
                objects[c].addS(i);
            }
            heights(obj.start.x, obj.start.y) = {i, obj.end.z + 1};
        }
    }
}

uint64_t part1() {
    parse();

    int result = 0;
    for(auto&& obj : objects) {
        auto ok = true;
        for(auto&& o : obj.above) {
            if(objects[o].below.size() == 1) {
                ok = false;
                break;
            }
        }
        result += ok;
    }

    return result;
}

uint64_t part2() {
    parse();

    uint64_t result = 0;

    std::vector<std::bitset<1024 + 512>> madeFall;
    madeFall.resize(objects.size());

    for(size_t i = 0; i < objects.size(); i++) {
        auto& el = objects[i];
        auto& s = madeFall[i];
        if(el.below.size() != 0) {
            s.set();
            for(auto&& a : el.below) {
                s &= madeFall[a];
            }
        } else {
            s.reset();
        }
        s.set(i);
        result += s.count() - 1;
    }

    return result;
}

static auto p1 = aoc::test(part1, 2023, 22, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 22, 2, "part2");

} // namespace y2023::Day22
