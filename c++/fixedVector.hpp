#pragma once
#include <array>
#include <span>

template <typename T, size_t _size>
class fixedVector {
   private:
    std::array<T, _size> data;
    uint32_t pos = 0;

   public:
    fixedVector() {}

    void push_back(const T& value) {
        data[pos] = value;
        pos++;
    }
    void pop_back() {
        pos--;
    }
    void erase(int index) {
        pos--;
        for (; index < pos; index++) {
            data[index] = data[index + 1];
        }
    }

    void clear() {
        for (size_t i = 0; i < pos; i++) {
            data[i].~T();
        }

        pos = 0;
    }
    auto size() const {
        return pos;
    }
    auto empty() const {
        return pos == 0;
    }
    constexpr size_t capacity() const {
        return _size;
    }
    auto back() {
        return data[pos - 1];
    }
    auto begin() {
        return data.begin();
    }
    auto end() {
        return data.begin() + pos;
    }
    operator std::span<T>() {
        return std::span<T>(data).subspan(0, pos);
    }

    T operator[](int index) const {
        return data[index];
    }
    T& operator[](int index) {
        return data[index];
    }
};
