#pragma once
#include <emmintrin.h>
#include <immintrin.h>

#include <fstream>
#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#define always__inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define always__inline __forceinline
#else
#define always__inline
#endif

std::string readFile(const char* path) {
    std::ifstream file(path);
    std::string res((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));
    return res;
}

std::vector<std::string> readLines(const char* path, bool skipEmpty = true) {
    std::ifstream file(path);
    std::vector<std::string> res;
    std::string line;

    while (file) {
        std::getline(file, line);
        if (skipEmpty && line.empty()) continue;
        res.push_back(line);
    }
    // TODO: somehow fails if no empty last line

    return res;
}

std::vector<std::string> split(const std::string& str, const char c) {
    std::vector<std::string> res;

    int start = 0;
    int pos = 0;

    while (pos < str.size()) {
        if (str[pos] == c) {
            res.push_back(str.substr(start, pos - start));
            start = pos + 1;
        }
        pos++;
    }
    res.push_back(str.substr(start, str.size() - start));

    return res;
}

bool inline isDigit(char c) {
    return c >= '0' && c <= '9';
}

template <int width, int height, typename T>
class Grid {
   public:
    std::array<T, width * height> data{0};

    Grid() = default;

    inline T operator()(int x, int y) const {
        return data[x + y * width];
    }

    inline T& operator()(int x, int y) {
        return data[x + y * width];
    }
};

template <typename T>
struct Point {
    T x;
    T y;

    Point() {}
    Point(T v) : x(v), y(v) {}
    Point(T x, T y) : x(x), y(y) {}

    Point<T>& operator+=(const Point<T>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point<T>& operator-=(const Point<T>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Point<T>& operator*=(const Point<T>& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    friend Point<T> operator+(Point<T> lhs, const Point<T>& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Point<T> operator-(Point<T> lhs, const Point<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend Point<T> operator*(Point<T> lhs, const Point<T>& rhs) {
        lhs *= rhs;
        return lhs;
    }
};

auto findChar(const char* str, char c) {
    const auto cmp_val = _mm256_set1_epi8(c);

    for (size_t i = 0;; i += 32) {
        auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)(str + i)), cmp_val));
        if (mask != 0) {
            return i + _tzcnt_u32(mask);
        }
    }
}
