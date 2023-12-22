#pragma once

template <typename T>
struct vec2 {
    T x;
    T y;

    vec2() {}
    vec2(T v) : x(v), y(v) {}
    vec2(T x, T y) : x(x), y(y) {}

    vec2<T> sign() {
        return {T((x > 0) - (x < 0)), T((y > 0) - (y < 0))};
    }
    auto length() {
        return std::sqrt(x * x + y * y);
    }

    vec2<T>& operator+=(const vec2<T>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    vec2<T>& operator-=(const vec2<T>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    vec2<T>& operator*=(const vec2<T>& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    vec2<T>& operator/=(const vec2<T>& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    friend vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend vec2<T> operator*(vec2<T> lhs, const vec2<T>& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend vec2<T> operator/(vec2<T> lhs, const vec2<T>& rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend bool operator==(const vec2<T>& lhs, const vec2<T>& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};
