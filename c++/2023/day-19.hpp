#pragma once
#include <array>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"
#include "../vec2.hpp"

namespace y2023::Day19 {

const auto input = aoc::getInput(2023, 19);

struct Rule {
    char prop;
    char comp;
    int num;
    int nextRule;
};

struct Part {
    // use vec2 as range caues i don't wanna make a new type
    vec2<int> x;
    vec2<int> m;
    vec2<int> a;
    vec2<int> s;
};

uint32_t readStr(size_t& pos) {
    uint32_t val = input[pos++];
    while(true) {
        auto c = input[pos++];
        if(c >= 'a' && c <= 'z') {
            val = (val << 8) | c;
        } else {
            break;
        }
    }
    return val;
}

std::array<std::vector<Rule>, 'z' | ('z' << 8) | ('z' << 16)> rules; // could be compressed to 26^3 entries
auto parseRules(size_t& pos) {
    while(true) {
        auto label = readStr(pos);

        auto& r = rules[label];
        r.clear(); // reuse old allocation

        while(true) {
            auto c = input[pos++];
            auto c1 = input[pos++];

            if(c1 == '>' || c1 == '<') {
                auto val = readUInt4(input, pos);
                auto next = readStr(pos);

                r.emplace_back(c, c1, val, next);
            } else {
                pos -= 2;
                auto next = readStr(pos);
                r.emplace_back(0, 0, 0, next);
                pos++;
                break;
            }
        }

        if(input[pos] == '\n') {
            pos++;
            break;
        }
    }
}

uint64_t part1() {
    size_t pos = 0;
    parseRules(pos);

    uint64_t result = 0;
    while(pos < input.size()) {
        pos += 3;
        auto x = readUInt4(input, pos);
        pos += 2;
        auto m = readUInt4(input, pos);
        pos += 2;
        auto a = readUInt4(input, pos);
        pos += 2;
        auto s = readUInt4(input, pos);
        pos++;

        auto l = ('i' << 8) | 'n';
        while(true) {
            if(l == 'A') {
                result += x + m + a + s;
                break;
            } else if(l == 'R') {
                break;
            }
            auto& r = rules[l];

            for(auto&& sub : r) {
                if(sub.prop == 0) {
                    l = sub.nextRule;
                    break;
                }
                int val;
                if(sub.prop == 'x') val = x;
                else if(sub.prop == 'm') val = m;
                else if(sub.prop == 'a') val = a;
                else if(sub.prop == 's') val = s;

                if((sub.comp == '>' && val > sub.num) || (sub.comp == '<' && val < sub.num)) {
                    l = sub.nextRule;
                    break;
                }
            }
        }
    }

    return result;
}

uint64_t count(int rule, Part p) {
    if(rule == 'A') {
        return (uint64_t)(p.x.y - p.x.x + 1) *
               (uint64_t)(p.m.y - p.m.x + 1) *
               (uint64_t)(p.a.y - p.a.x + 1) *
               (uint64_t)(p.s.y - p.s.x + 1);
    } else if(rule == 'R') {
        return 0;
    }
    auto& r = rules[rule];

    uint64_t c = 0;
    for(auto&& sub : r) {
        if(sub.prop == 0) {
            c += count(sub.nextRule, p);
            break;
        }

        vec2<int>* val = nullptr;
        if(sub.prop == 'x') val = &p.x;
        else if(sub.prop == 'm') val = &p.m;
        else if(sub.prop == 'a') val = &p.a;
        else if(sub.prop == 's') val = &p.s;

        auto old = *val;

        if(sub.comp == '<') {
            *val = {old.x, sub.num - 1};
            old.x = sub.num;
        } else {
            *val = {sub.num + 1, old.y};
            old.y = sub.num;
        }

        c += count(sub.nextRule, p);
        *val = old;
    }
    return c;
}

uint64_t part2() {
    size_t pos = 0;
    parseRules(pos);
    return count(('i' << 8) | 'n', Part{{1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}});
}

static auto p1 = aoc::test(part1, 2023, 19, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 19, 2, "part2");

} // namespace y2023::Day19
