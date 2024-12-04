#pragma once
#include <vector>

#include "../util.hpp"

namespace y2024::Day2 {

const auto input = readFile("../data/2024/day2.txt");

auto parse() {
    std::vector<std::vector<int>> r;
    r.reserve(1000);

    size_t i = 0;
    while (i < input.size()) {
        std::vector<int> v;
        while (true) {
            v.push_back(readUInt(input, i));
            if (input[i - 1] == '\n') break;
        }
        r.push_back(std::move(v));
    }
    return r;
}
auto lines = parse();

int test(std::vector<int>& line) {
    if (line[0] <= line[line.size() - 1]) {
        for (int i = 1; i < line.size(); i++) {
            auto a = line[i - 1];
            auto b = line[i];
            if (a >= b || (b - a) > 3) return 0;
        }
    } else {
        for (int i = 1; i < line.size(); i++) {
            auto a = line[i - 1];
            auto b = line[i];
            if (a <= b || (a - b) > 3) return 0;
        }
    }
    return 1;
}

uint64_t part1() {
    uint64_t result = 0;
    for (int i = 0; i < lines.size(); i++) {
        result += test(lines[i]);
    }
    return result;
}

bool testDescending(std::vector<int>& line) {
    auto t = [&](int a, int  b) {
        return a > b && (a - b) <= 3;
    };
    auto cont = [&](int i) {
        for (; i < line.size() - 1; i++) {
            if (!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    };

    for (int i = 0; i < line.size() - 1; i++) {
        auto a = line[i];
        auto b = line[i + 1];
        if (!t(a, b)) {
            // try skipping the left
            if ((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if (i == line.size() - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}
bool testAscending(std::vector<int>& line) {
    auto t = [&](int a, int  b) {
        return a < b && (b - a) <= 3;
    };
    auto cont = [&](int i) {
        for (; i < line.size() - 1; i++) {
            if (!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    };

    for (int i = 0; i < line.size() - 1; i++) {
        auto a = line[i];
        auto b = line[i + 1];
        if (!t(a, b)) {
            // try skipping the left
            if ((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if (i == line.size() - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}

uint64_t part2() {
    uint64_t result = 0;

    for (int i = 0; i < lines.size(); i++) {
        auto& line = lines[i];

        if (line[0] > line[line.size() - 1] || line[1] > line[line.size() - 1] || line[0] > line[line.size() - 2]) {
            if (testDescending(line)) {
                result++;
                continue;
            }
        }
        if (line[0] < line[line.size() - 1] || line[1] < line[line.size() - 1] || line[0] < line[line.size() - 2]) {
            if (testAscending(line)) {
                result++;
                continue;
            }
        }
    }

    return result;
}

}  // namespace y2024::Day2
