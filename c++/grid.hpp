#pragma once
#include "vec2.hpp"

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
    inline T operator()(vec2<V> pos) const {
        return data[pos.x + pos.y * width];
    }
    template <typename V>
    inline T& operator()(vec2<V> pos) {
        return data[pos.x + pos.y * width];
    }
};
