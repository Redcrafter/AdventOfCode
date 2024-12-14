#pragma once
#include <array>
#include <ranges>
#include <string>
#include <vector>

#include "../aoc.hpp"
#include "../util.hpp"
#include "../vec2.hpp"

namespace y2021::Day13 {

using Pos = vec2<int>;

struct Fold {
    char dir;
    int num;
};

struct Data {
    std::vector<Pos> points;
    std::vector<Fold> folds;
};

class Grid {
  private:
    static const int w = 2048;
    static const int h = 1024;

  public:
    std::array<uint8_t, w * h> data{};
    int width = 0;
    int height = 0;

    Grid(const Data& d) {
        for(auto p : d.points) {
            width = std::max(width, p.x);
            height = std::max(height, p.y);
        }
        width += 1;
        height += 1;
        // data.resize(width * height);

        for(auto p : d.points) {
            (*this)(p.x, p.y) = 1;
        }
    }

    uint8_t operator()(int x, int y) const {
        return data[x + y * w];
    }
    uint8_t& operator()(int x, int y) {
        return data[x + y * w];
    }
};

Data parseInput() {
    auto input = aoc::getInput(2021, 13);

    Data d{};

    for(auto&& str : std::ranges::split_view(input, '\n')) {
        if(isDigit(str[0])) {
            auto stuff = split(std::string_view(str), ',');
            d.points.push_back({parseInt<int>(stuff[0]), parseInt<int>(stuff[1])});
        } else if(!str.empty()) {
            d.folds.push_back({str[11], parseInt<int>(std::string_view(str).substr(13))});
        }
    }

    return d;
}

const auto d = parseInput();

uint64_t part1() {
    Grid g{d};

    int count = 0;
    for(int y = 0; y < g.height; y++) {
        for(int x = 0; x < 655; x++) {
            count += (g(x, y) |= g(1310 - x, y));
        }
    }
    return count;
}

std::string part2() {
    Grid g{d};

    auto foldX = [&](int foldX) {
        for(int y = 0; y < g.height; y++) {
            for(int x = 0; x < foldX; x++) {
                g(x, y) |= g(foldX * 2 - x, y);
            }
        }
        g.width = foldX;
    };
    auto foldY = [&](int foldY) {
        for(int y = 0; y < foldY; y++) {
            for(int x = 0; x < g.width; x++) {
                g(x, y) |= g(x, foldY * 2 - y);
            }
        }
        g.height = foldY;
    };

    for(auto el : d.folds) {
        if(el.dir == 'x')
            foldX(el.num);
        else
            foldY(el.num);
    }

    std::string str = "";
    for(int y = 0; y < g.height; y++) {
        for(int x = 0; x < g.width; x++) {
            if(g(x, y)) {
                str += "#";
            } else {
                str += ".";
            }
        }
        str += "\n";
    }
    return str;
}

static auto p1 = aoc::test(part1, 2021, 13, 1, "part1");
static auto p2 = aoc::test(part2, 2021, 13, 2, "part2");

} // namespace y2021::Day13
