#pragma once
#include <array>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2023::Day15 {

const auto input = aoc::getInput(2023, 15);

uint64_t part1() {
    uint64_t result = 0;

    size_t pos = 0;
    while(pos < input.length()) {
        uint64_t raw = *(uint32_t*)(input.data() + pos);
        pos += 4;

        int hash;
        if((raw >> 24) == ',') {
            hash = (raw & 0xFF) * 4913 + ((raw >> 8) & 0xFF) * 289 + (raw >> 16) * 17;
        } else {
            hash = (raw & 0xFF) * 83521 + ((raw >> 8) & 0xFF) * 4913 + ((raw >> 16) & 0xFF) * 289 + (raw >> 24) * 17;
            while(pos < input.length()) {
                char c = input[pos++];
                if(c == ',') break;
                hash = (hash + c) * 17;
            }
        }
        result += hash & 0xFF;
    }

    return result;
}

struct El {
    uint64_t label;
    char lense;
};

uint64_t part2() {
    std::array<fixedVector<El, 9>, 256> boxes;

    size_t pos = 0;
    while(pos < input.length()) {
        uint64_t raw = *(uint16_t*)(input.data() + pos);
        int hash = (raw & 0xFF) * 289 + (raw >> 8) * 17;

        pos += 2;

        char c;
        while(true) {
            c = input[pos++];
            if(c <= '=') break;
            hash = (hash + c) * 17;
            raw = (raw << 8) | c;
        }

        auto& b = boxes[hash & 0xFF];

        int i = 0;
        for(; i < b.size(); i++) {
            if(b[i].label == raw) {
                break;
            }
        }

        if(c == '=') {
            if(i < b.size()) {
                b[i].lense = input[pos];
            } else {
                b.push_back({raw, input[pos]});
            }
            pos += 2;
        } else {
            if(i < b.size()) {
                b.erase(i);
            }
            pos += 1;
        }
    }

    uint64_t result = 0;
    for(size_t i = 0; i < boxes.size(); i++) {
        auto& box = boxes[i];
        for(size_t j = 0; j < box.size(); j++) {
            result += (i + 1) * (j + 1) * (box[j].lense - '0');
        }
    }
    return result;
}

static auto p1 = aoc::test(part1, 2023, 15, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 15, 2, "part2");

} // namespace y2023::Day15
