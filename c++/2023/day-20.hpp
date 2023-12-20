#pragma once
#include <array>
#include <unordered_map>
#include <vector>

#include "../util.hpp"

namespace y2023::Day20 {

const auto input = readFile("../data/2023/day20.txt");

struct El {
    std::vector<uint16_t> dest;
    uint8_t type = 0;
};

std::array<El, 'zz'> map;

always__inline void parse() {
    size_t pos = 0;
    while (pos < input.size()) {
        auto c = input[pos++];

        El* el;
        if (c == '&') {
            auto label = *(uint16_t*)(input.data() + pos);
            el = &map[label];
            el->type = '&';
            pos += 4;
        } else if (c == '%') {
            auto label = *(uint16_t*)(input.data() + pos);
            el = &map[label];
            el->type = '%';
            pos += 4;
        } else {  // broadcast
            el = &map[0];
            el->type = 'b';
            pos += 12;
        }

        el->dest.clear();
        while (input[pos] != '\n') {
            pos += 2;
            el->dest.push_back(*(uint16_t*)(input.data() + pos));
            pos += 2;
        }
        pos++;
    }
}

uint64_t part1() {
    parse();

    std::unordered_map<uint16_t, std::unordered_map<int, bool>> states;
    std::vector<std::tuple<uint16_t, uint16_t, bool>> stack;

    for (size_t i = 0; i < map.size(); i++) {
        for (auto j : map[i].dest) {
            auto t = map[j];
            if (t.type == '&') {
                states[j][i] = false;
            }
        }
    }

    int lc = 0;
    int hc = 0;
    auto& targets = map[0].dest;

    for (size_t i = 0; i < 1000; i++) {
        lc++;
        stack.clear();

        for (auto i : targets) {
            stack.emplace_back(i, 0, false);
        }

        for (size_t i = 0; i < stack.size(); i++) {
            auto [dest, src, high] = stack[i];

            if (high)
                hc++;
            else
                lc++;

            auto& el = map[dest];

            if (el.type == '&') {
                auto& mem = states[dest];
                mem[src] = high;

                auto s = !std::all_of(mem.begin(), mem.end(), [](auto& v) { return std::get<1>(v); });
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, s);
                }
            } else if (el.type == '%') {
                if (high)
                    continue;
                el.type = ('%' | 128);
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, true);
                }
            } else if (el.type == ('%' | 128)) {
                if (high)
                    continue;
                el.type = '%';
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, false);
                }
            }
        }
    }

    return lc * hc;
}

uint64_t part2() {
    parse();

    std::unordered_map<uint16_t, std::unordered_map<int, bool>> states;
    std::vector<std::tuple<uint16_t, uint16_t, bool>> stack;

    uint16_t rx;
    std::vector<uint16_t> ends;

    for (size_t i = 0; i < map.size(); i++) {
        for (auto j : map[i].dest) {
            auto t = map[j];
            if (t.type == '&') {
                states[j][i] = false;
            }
            if (j == 'xr') {
                rx = i;
            }
        }
    }
    for (size_t i = 0; i < map.size(); i++) {
        for (auto j : map[i].dest) {
            if (j == rx) {
                ends.push_back(i);
            }
        }
    }

    auto& targets = map[0].dest;
    uint64_t result = 1;
    int count = 0;

    for (size_t j = 1; count != ends.size(); j++) {
        stack.clear();

        for (auto i : targets) {
            stack.emplace_back(i, 0, false);
        }

        for (size_t i = 0; i < stack.size(); i++) {
            auto [dest, src, high] = stack[i];

            auto& el = map[dest];

            if (el.type == '&') {
                auto& mem = states[dest];
                mem[src] = high;

                auto s = !std::all_of(mem.begin(), mem.end(), [](auto& v) { return std::get<1>(v); });
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, s);
                }

                if (!high && std::any_of(ends.begin(), ends.end(), [&](auto& v) { return v == dest; })) {
                    count++;
                    result *= j;
                }
            } else if (el.type == '%') {
                if (high)
                    continue;
                el.type = ('%' | 128);
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, true);
                }
            } else if (el.type == ('%' | 128)) {
                if (high)
                    continue;
                el.type = '%';
                for (auto&& sub : el.dest) {
                    stack.emplace_back(sub, dest, false);
                }
            }
        }
    }

    return result;
}

uint64_t part1_cheat() {
    parse();

    uint64_t lc = 1000;  // initial fire
    uint64_t hc = 0;

    for (auto t : map[0].dest) {
        uint16_t center;
        auto& el = map[t];
        if (map[el.dest[0]].type == '&') {
            center = el.dest[0];
        } else {
            center = el.dest[1];
        }
        uint16_t centerSize = map[center].dest.size();

        int n = 1000;
        while (n != 0) {
            auto& el = map[t].dest;

            auto low = n / 2;
            auto high = (n + 1) / 2;

            if (el.size() == 2) {
                hc += high * 2 + n * (1 + centerSize);
                lc += low * 2 + n;
            } else {
                lc += low;
                hc += high;
            }

            t = el[0] == center ? el[1] : el[0];
            n = low;
        }
        lc += 1000;
    }

    return lc * hc;
}

uint64_t part2_cheat() {
    parse();

    uint64_t result = 1;
    for (auto t : map[0].dest) {
        uint16_t center;
        auto& el = map[t];
        if (map[el.dest[0]].type == '&') {
            center = el.dest[0];
        } else {
            center = el.dest[1];
        }

        int n = 1 << 11;
        for (size_t i = 0; i < 11; i++) {
            auto& el = map[t].dest;
            auto c0 = el[0] == center;
            n |= (c0 || el.size() == 2) << i;
            t = (c0) ? el[1] : el[0];
        }
        result *= n;
    }

    return result;
}

}  // namespace y2023::Day20
