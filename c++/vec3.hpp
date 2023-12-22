#pragma once

template <typename T>
struct vec3 {
    T x;
    T y;
    T z;

    vec3() {}
    vec3(T v) : x(v), y(v) {}
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    vec3<T> sign() {
        return {T((x > 0) - (x < 0)), T((y > 0) - (y < 0)), T((z > 0) - (z < 0))};
    }

    vec3<T>& operator+=(const vec3<T>& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    vec3<T>& operator-=(const vec3<T>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    vec3<T>& operator*=(const vec3<T>& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }
    vec3<T>& operator/=(const vec3<T>& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    friend vec3<T> operator+(vec3<T> lhs, const vec3<T>& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend vec3<T> operator-(vec3<T> lhs, const vec3<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend vec3<T> operator*(vec3<T> lhs, const vec3<T>& rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend vec3<T> operator/(vec3<T> lhs, const vec3<T>& rhs) {
        lhs /= rhs;
        return lhs;
    }
    friend bool operator==(const vec3<T>& lhs, const vec3<T>& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }
};
