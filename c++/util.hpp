#pragma once
#include <emmintrin.h>
#include <immintrin.h>

#include <bit>
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

template <typename T>
struct Point {
    T x;
    T y;

    Point() {}
    Point(T v) : x(v), y(v) {}
    Point(T x, T y) : x(x), y(y) {}

    Point<T> sign() {
        return {T((x > 0) - (x < 0)), T((y > 0) - (y < 0))};
    }

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
    friend bool operator==(const Point<T>& lhs, const Point<T>& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

template <int width, int height, typename T>
class Grid {
   public:
    std::array<T, width * height> data;

    Grid() = default;

    void fill(T val) {
        data.fill(val);
    }
    inline T operator()(int x, int y) const {
        return data[x + y * width];
    }
    inline T& operator()(int x, int y) {
        return data[x + y * width];
    }
    template <typename V>
    inline T operator()(Point<V> pos) const {
        return data[pos.x + pos.y * width];
    }
    template <typename V>
    inline T& operator()(Point<V> pos) {
        return data[pos.x + pos.y * width];
    }
};

template <typename T>
class DynGrid {
   private:
    T* data;
    int _width;
    int _height;
    int _capacity;

   public:
    DynGrid(int width, int height) : _width(width), _height(height), _capacity(width * height) {
        data = new T[width * height];
    }
    ~DynGrid() {
        delete[] data;
    }

    void fill(T val) {
        std::fill_n(data, _width * _height, val);
    }
    void reserve(int width, int height) {
        auto s = width * height;
        if (_capacity < s) {
            delete[] data;
            data = new T[width * height];
            _capacity = s;
        }
        _width = width;
        _height = height;
    }

    inline T operator()(int x, int y) const {
        return data[x + y * _width];
    }
    inline T& operator()(int x, int y) {
        return data[x + y * _width];
    }
};

template <typename T, size_t _size>
class FixedVector {
   private:
    std::array<T, _size> data;
    uint32_t pos = 0;

   public:
    FixedVector() {}

    void push_back(const T& value) {
        data[pos] = value;
        pos++;
    }
    void erase(int index) {
        pos--;
        for (; index < pos; index++) {
            data[index] = data[index + 1];
        }
    }
    auto size() const {
        return pos;
    }
    constexpr size_t capacity() const {
        return _size;
    }

    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }
};

auto findChar(const char* str, char c) {
    const auto cmp_val = _mm256_set1_epi8(c);

    for (size_t i = 0;; i += 32) {
        auto mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256((__m256i*)(str + i)), cmp_val));
        if (mask != 0) {
            return i + std::countr_zero((uint32_t)mask);
        }
    }
}

template <typename T>
bool contains(const std::span<const T> arr, T search) {
    bool ok = false;
    for (auto& i : arr) {
        ok |= i == search;
    }
    return ok;
}

template <typename T>
bool contains(const T* ptr, int start, int end, T search) {
    bool ok = false;
    for (size_t i = start; i < end; i++) {
        ok |= ptr[i] == search;
    }
    return ok;
}
