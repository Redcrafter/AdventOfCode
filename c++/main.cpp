#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#ifdef _MSC_VER
#include <windows.h>
// y u do this windows
#undef min
#undef max
#endif

#include "./2021/day-1.hpp"
#include "./2021/day-11-bit.hpp"
#include "./2021/day-11.hpp"
#include "./2021/day-12.hpp"
#include "./2021/day-13.hpp"
#include "./2021/day-20.hpp"
#include "./2021/day-21.hpp"
#include "./2021/day-7.hpp"

template <class T>
inline void DoNotOptimize(const T& value) {
    asm volatile(""
                 :
                 : "r,m"(value)
                 : "memory");
}

template <class T>
inline void DoNotOptimize(T& value) {
#if defined(__clang__)
    asm volatile(""
                 : "+r,m"(value)
                 :
                 : "memory");
#else
    asm volatile(""
                 : "+m,r"(value)
                 :
                 : "memory");
#endif
}

template <typename R>
float test(R(func)()) {
    std::chrono::nanoseconds time{};
    int i = 0;
    while (i < 100000 && time < std::chrono::seconds(10)) {  // time < std::chrono::seconds(2)
        auto start = std::chrono::high_resolution_clock::now();
        auto val = func();
        DoNotOptimize(val);
        auto end = std::chrono::high_resolution_clock::now();

        time += end - start;

        i++;
    }

    return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(time).count() / i;
}

struct Test {
    int Day;
    int Part;
    uint64_t (*func)();
    uint64_t expected;
};

int main() {
#ifdef _MSC_VER
    SetConsoleOutputCP(65001);
#endif

    Test idk[] = {
        {1, 1, Day1::part1, 1226},
        {1, 2, Day1::part2, 1252},
        {7, 1, Day7::func<1>, 336131},
        {7, 2, Day7::func<2>, 92676646},
        {11, 1, Day11::func<1>, 1739},
        {11, 2, Day11::func<2>, 324},
        {11, 1, Day11_bit::part1, 1739},
        {11, 2, Day11_bit::part2, 324},
        {13, 1, Day13::part1, 751},
        // {13, 2, Day13::part2, N/A},
        {20, 2, Day20::part2, 19492},
        {21, 1, Day21::part1, 576600},
        {21, 2, Day21::part2, 131888061854776},
    };

    for (auto&& i : idk) {
        auto res = i.func();
        if (res != i.expected) {
            std::cout << "Assertion failed " << i.Day << "-" << i.Part << " " << res << " != " << i.expected << std::endl;
        }

        std::cout << "Day " << i.Day << "-" << i.Part << " took " << test(i.func) << "μs" << std::endl;
    }

    std::cout << "Day 13-2 took " << test(Day13::part2) << "μs" << std::endl;

    return 0;
}
