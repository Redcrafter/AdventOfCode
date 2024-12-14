#pragma once
#include <array>

#include "../aoc.hpp"
#include "../fixedVector.hpp"

namespace y2024::Day2 {

const auto input = aoc::getInput(2024, 2);

auto parse() {
    std::array<fixedVector<int, 8>, 1000> r{};

    size_t pos = 0;
    for(int i = 0; pos < input.size(); i++) {
        while(true) {
            auto c0 = input[pos];
            auto c1 = input[pos + 1];

            if(c1 == '\n' || c1 == ' ') {
                r[i].push_back(c0 & 0xF);
                pos += 2;
                if(c1 == '\n') break;
            } else {
                r[i].push_back((c0 & 0xF) * 10 + (c1 & 0xF));
                pos += 3;
                if(input[pos - 1] == '\n') break;
            }
        }
    }
    return r;
}
auto lines = parse();

int test(fixedVector<int, 8>& line) {
    if(line[0] <= line[line.size() - 1]) {
        for(int i = 1; i < line.size(); i++) {
            auto a = line[i - 1];
            auto b = line[i];
            if(a >= b || (b - a) > 3) return 0;
        }
    } else {
        for(int i = 1; i < line.size(); i++) {
            auto a = line[i - 1];
            auto b = line[i];
            if(a <= b || (a - b) > 3) return 0;
        }
    }
    return 1;
}

uint64_t part1() {
    uint64_t result = 0;
    for(int i = 0; i < lines.size(); i++) {
        result += test(lines[i]);
    }
    return result;
}

bool testDescending(fixedVector<int, 8>& line) {
    auto t = [&](int a, int b) {
        return a > b && (a - b) <= 3;
    };
    auto cont = [&](int i) {
        for(; i < line.size() - 1; i++) {
            if(!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    };

    for(int i = 0; i < line.size() - 1; i++) {
        auto a = line[i];
        auto b = line[i + 1];
        if(!t(a, b)) {
            // try skipping the left
            if((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if(i == line.size() - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}
bool testAscending(fixedVector<int, 8>& line) {
    auto t = [&](int a, int b) {
        return a < b && (b - a) <= 3;
    };
    auto cont = [&](int i) {
        for(; i < line.size() - 1; i++) {
            if(!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    };

    for(int i = 0; i < line.size() - 1; i++) {
        auto a = line[i];
        auto b = line[i + 1];
        if(!t(a, b)) {
            // try skipping the left
            if((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if(i == line.size() - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}

uint64_t part2() {
    uint64_t result = 0;

    for(int i = 0; i < lines.size(); i++) {
        auto& line = lines[i];

        if(line[0] > line[line.size() - 1] || line[1] > line[line.size() - 1] || line[0] > line[line.size() - 2]) {
            if(testDescending(line)) {
                result++;
                continue;
            }
        }
        if(line[0] < line[line.size() - 1] || line[1] < line[line.size() - 1] || line[0] < line[line.size() - 2]) {
            if(testAscending(line)) {
                result++;
                continue;
            }
        }
    }

    return result;
}

static auto p1 = aoc::test(part1, 2024, 2, 1, "part1");
static auto p2 = aoc::test(part2, 2024, 2, 2, "part2");

} // namespace y2024::Day2
