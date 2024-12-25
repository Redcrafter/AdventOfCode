#pragma once
#include <array>
#include <cassert>
#include <cstdint>

template<std::integral Tkey, size_t capacity>
class FlatSet {
  public:
    static constexpr Tkey empty = -1;

    std::array<Tkey, capacity> data;
    size_t used;

    FlatSet() {
        used = 0;
        data.fill(empty);
    }

    void clear() {
        if(used == 0) return;
        data.fill(empty);
        used = 0;
    }
    auto size() const {
        return used;
    }
    void insert(Tkey i) {
        assert(i != empty);
        assert(used < capacity);

        auto x = (i * 0x45d9f3b) % data.size();
        while(true) {
            auto& v = data[x];

            if(v == i) return;
            if(v == empty) {
                v = i;
                used++;
                return;
            }
            x = (x + 1) % data.size();
        }
    }
    /*
    // todo implement if needed. simple implemntation does not work because elements after the erased one have to be re inserted to not leave gaps
    void erase(Tkey i) {
        assert(i != empty);

        auto x = (i * 0x45d9f3b) % data.size();
        while(true) {
            auto& v = data[x];

            if(v == i) {
                v = empty;
                used--;
                return;
            }
            if(v == empty) return;
            x = (x + 1) % data.size();
        }
    }*/
    bool contains(Tkey i) const {
        assert(i != empty);

        auto start = (i * 0x45d9f3b) % data.size();
        auto x = start;
        do {
            auto& v = data[x];

            if(v == i) return true;
            if(v == empty) return false;
            x = (x + 1) % data.size();
        } while(x != start);
        return false;
    }
};
