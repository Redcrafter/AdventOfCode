#pragma once
#include <string>
#include <vector>

namespace y2021::Day13 {

struct Pos {
    int x;
    int y;
};

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
    std::array<uint8_t, w * h> data{0};
    int width = 0;
    int height = 0;

    Grid(const Data& d) {
        for (auto p : d.points) {
            width = std::max(width, p.x);
            height = std::max(height, p.y);
        }
        width += 1;
        height += 1;
        // data.resize(width * height);

        for (auto p : d.points) {
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
    auto input = readLines("../data/2021/day13.txt");

    Data d{};

    size_t last = 0;
    size_t next = 0;

    for (auto&& str : input) {
        if (isDigit(str[0])) {
            auto stuff = split(str, ',');

            d.points.push_back({std::stoi(stuff[0]), std::stoi(stuff[1])});
        } else if (str.length() != 0) {
            d.folds.push_back({str[11], std::stoi(str.substr(13))});
        }
    }

    return d;
}

const auto d = parseInput();

uint64_t part1() {
    Grid g{d};

    int count = 0;
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < 655; x++) {
            count += (g(x, y) |= g(1310 - x, y));
        }
    }
    return count;
}

std::string part2() {
    Grid g{d};

    auto foldX = [&](int foldX) {
        for (int y = 0; y < g.height; y++) {
            for (int x = 0; x < foldX; x++) {
                g(x, y) |= g(foldX * 2 - x, y);
            }
        }
        g.width = foldX;
    };
    auto foldY = [&](int foldY) {
        for (int y = 0; y < foldY; y++) {
            for (int x = 0; x < g.width; x++) {
                g(x, y) |= g(x, foldY * 2 - y);
            }
        }
        g.height = foldY;
    };

    for (auto el : d.folds) {
        if (el.dir == 'x')
            foldX(el.num);
        else
            foldY(el.num);
    }

    std::string str = "";
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            if (g(x, y)) {
                str += "#";
            } else {
                str += ".";
            }
        }
        str += "\n";
    }
    return str;
}

}  // namespace y2021::Day13
