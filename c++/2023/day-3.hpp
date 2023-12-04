#pragma once
#include <array>
#include <iostream>

#include "../util.hpp"

namespace y2023::Day3 {

const auto input = readFile("../data/2023/day3.txt");
const int width = 141;  // 140 chars + newline

bool isSymbol(char c) {
    return c == '*' ||
           c == '@' ||
           c == '-' ||
           c == '+' ||
           c == '#' ||
           c == '%' ||
           c == '=' ||
           c == '/' ||
           c == '$' ||
           c == '&';
}

bool checkEdge(int pos, int len) {
    for (int x1 = -1; x1 <= len; x1++) {
        if (pos > width && isSymbol(input[pos - width + x1]))
            return true;
        if (pos < (width * 139) && isSymbol(input[pos + width + x1]))
            return true;
    }

    if (isSymbol(input[pos - 1]))
        return true;
    if (isSymbol(input[pos + len]))
        return true;

    return false;
}

uint64_t part1() {
    uint64_t result = 0;

    size_t pos = 0;
    while (pos < input.length()) {
        auto c = input[pos++];

        if (!isDigit(c)) 
            continue;

        int start = pos;
        int num = c - '0';
        while (isDigit(c = (input[pos++]))) {
            num = num * 10 + c - '0';
        }

        if (checkEdge(start - 1, pos - start)) {
            result += num;
        }
    }

    return result;
}

uint64_t part2() {
    uint64_t result = 0;

    for (size_t pos = 0; pos < input.length(); pos++) {
        if (input[pos] != '*')
            continue;

        int n1 = 0;
        // int n2 = 0;

        for (int y = -width; y <= width; y += width) {
            for (int x = -1; x <= 1;) {
                int s = pos + y + x;
                auto c = input[s];

                if (isDigit(c)) {
                    s--;

                    // find start
                    while (isDigit(input[s])) s--;
                    s++;

                    // read value
                    int v = 0;
                    while (isDigit(c = input[s])) {
                        v = v * 10 + c - '0';
                        s++;
                    }
                    if (n1) {
                        result += n1 * v;
                        goto end;
                    } else
                        n1 = v;

                    x = s - (pos + y);
                } else {
                    x++;
                }
            }
        }

    end:
    }

    return result;
}

}  // namespace y2023::Day3
