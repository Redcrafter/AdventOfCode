#include <algorithm>
#include <chrono>
#include <iostream>
#include <tuple>
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

#include "./2022/day-6.hpp"
#include "./2022/day-7.hpp"
#include "./2022/day-8.hpp"

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

auto toMicro(const std::chrono::nanoseconds& time) {
    return std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(time).count();
}

template <typename R>
auto test(R(func)()) {
    std::chrono::nanoseconds time{};
    std::chrono::nanoseconds min {999999999999999999llu};
    std::chrono::nanoseconds max {0};
    int i = 0;
    while (time < std::chrono::seconds(20)) {  // i < 100000 && time < std::chrono::seconds(2)
        auto start = std::chrono::high_resolution_clock::now();
        auto val = func();
        DoNotOptimize(val);
        auto end = std::chrono::high_resolution_clock::now();

        auto dt = end - start;

        if(dt < min) min = dt;
        if(dt > max) max = dt;
        time += dt;

        i++;
    }

    return std::tuple(toMicro(min), toMicro(max), toMicro(time) / i);
}

struct Test {
    int Year;
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
        {2021, 1, 1, Day1::part1, 1226},
        {2021, 1, 2, Day1::part2, 1252},
        {2021, 7, 1, Day7::func<1>, 336131},
        {2021, 7, 2, Day7::func<2>, 92676646},
        {2021, 11, 1, Day11::func<1>, 1739},
        {2021, 11, 2, Day11::func<2>, 324},
        {2021, 11, 1, Day11_bit::part1, 1739},
        {2021, 11, 2, Day11_bit::part2, 324},
        {2021, 13, 1, Day13::part1, 751},
        // {2021, 13, 2, Day13::part2, N/A},
        {2021, 20, 2, Day20::part2, 19492},
        {2021, 21, 1, Day21::part1, 576600},
        {2021, 21, 2, Day21::part2, 131888061854776},

        {2022, 6, 1, y2022::Day6::part1, 1953},
        {2022, 6, 2, y2022::Day6::part2, 2301},
        {2022, 7, 1, y2022::Day7::part1, 1667443},
        {2022, 7, 2, y2022::Day7::part2, 8998590},
        {2022, 8, 1, y2022::Day8::part1, 1859},
        {2022, 8, 2, y2022::Day8::part2, 332640}
    };

    for (auto&& i : idk) {
        auto res = i.func();
        if (res != i.expected) {
            std::cout << "Assertion failed " << i.Year << "-" << i.Day << "-" << i.Part << " " << res << " != " << i.expected << std::endl;
        }

        auto [min,max,avg] = test(i.func);
        std::cout << "Day " << i.Year << "-" << i.Day << "-" << i.Part << " took " << min << "μs/" << max << "μs/" << avg << "μs" << std::endl;
    }

    auto [min,max,avg] = test(Day13::part2);
    std::cout << "Day 2021-13-2 took" << min << "μs/" << max << "μs/" << avg << "μs" << std::endl;

    return 0;
}
