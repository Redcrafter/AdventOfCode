#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <span>
#include <tuple>
#include <vector>

#include "days.hpp"

template <class T>
inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

template <class T>
inline void DoNotOptimize(T& value) {
#if defined(__clang__)
    asm volatile("" : "+r,m"(value) : : "memory");
#else
    asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

template <typename R>
auto test(R(func)()) {
    std::chrono::nanoseconds time{};
    std::vector<std::chrono::duration<double, std::nano>> times;

    // time 1 run to determine loop count
    auto start = std::chrono::high_resolution_clock::now();
    auto val = func();
    DoNotOptimize(val);
    auto end = std::chrono::high_resolution_clock::now();

    // make it so 1 sample step takes ~100ms
    const auto runs = std::ceil((100 * 1000 * 1000.0) / (end - start).count());

    int i = 0;
    while (time < std::chrono::seconds(5)) {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < runs; i++) {
            auto val = func();
            DoNotOptimize(val);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto dt = (end - start);
        time += dt;
        times.push_back(dt / (double)runs);

        i++;
    }

    return std::tuple(time / (double)(i * runs), times);
}

struct Test {
    const char* name;
    uint64_t (*func)();
    uint64_t expected;
};

template <typename T>
auto median(const std::span<T>& arr) {
    auto mid = arr.size() / 2;
    if (arr.size() % 2 == 0) {
        return (arr[mid - 1] + arr[mid]) / 2;
    } else {
        return arr[mid];
    }
}

std::string formatTime(std::chrono::duration<double, std::nano> value) {
    // clang does not support std::format yet. come on
    char buf[256];
    if (value < std::chrono::microseconds(1)) {
        sprintf(buf, "%7.2fns", value.count());
    } else if (value < std::chrono::milliseconds(1)) {
        sprintf(buf, "%7.2fμs", value.count() / 1e3);
    } else if (value < std::chrono::seconds(1)) {
        sprintf(buf, "%7.2fms", value.count() / 1e6);
    } else {
        sprintf(buf, "%7.2fs ", value.count() / 1e9);
    }
    return buf;
}

#define entry(func, result) { #func, func, result }

int main() {
#ifdef _MSC_VER
    SetConsoleOutputCP(65001);
#endif

    Test idk[] = {
        entry(y2021::Day1::part1, 1226),
        entry(y2021::Day1::part2, 1252),
        entry(y2021::Day7::func<1>, 336131),
        entry(y2021::Day7::func<2>, 92676646),
        entry(y2021::Day11::func<1>, 1739),
        entry(y2021::Day11::func<2>, 324),
        entry(y2021::Day11_bit::part1, 1739),
        entry(y2021::Day11_bit::part2, 324),
        entry(y2021::Day13::part1, 751),
        // entry(y2021::Day13::part2, N/A),
        entry(y2021::Day20::part2, 19492),
        entry(y2021::Day21::part1, 576600),
        entry(y2021::Day21::part2, 131888061854776),

        entry(y2022::Day6::part1, 1953),
        entry(y2022::Day6::part2, 2301),
        entry(y2022::Day7::part1, 1667443),
        entry(y2022::Day7::part2, 8998590),
        entry(y2022::Day8::part1, 1859),
        entry(y2022::Day8::part2, 332640),
        entry(y2022::Day9::part1, 5981),
        entry(y2022::Day9::part2, 2352),
        entry(y2022::Day12::part1, 528),
        entry(y2022::Day12::part2, 522),

        entry(y2023::Day1::part1, 52974),
        entry(y2023::Day1::part2, 53340),
        entry(y2023::Day2::part1, 3059),
        entry(y2023::Day2::part2, 65371),
        entry(y2023::Day3::part1, 531561),
        entry(y2023::Day3::part2, 83279367),
        entry(y2023::Day4::part1, 21138),
        entry(y2023::Day4::part2, 7185540),
        entry(y2023::Day5::part1, 650599855),
        entry(y2023::Day5::part2, 1240035),
        entry(y2023::Day6::part1, 1159152),
        entry(y2023::Day6::part2, 41513103),
        entry(y2023::Day6::part2_dumb, 41513103),
        entry(y2023::Day7::part1, 249748283),
        entry(y2023::Day7::part2, 248029057),
        entry(y2023::Day8::part1, 12599),
        entry(y2023::Day8::part1_cheat, 12599),
        entry(y2023::Day8::part2, 8245452805243),
        entry(y2023::Day8::part2_cheat, 8245452805243),
        entry(y2023::Day9::part1, 1969958987),
        entry(y2023::Day9::part1_math, 1969958987),
        entry(y2023::Day9::part1_sum, 1969958987),
        entry(y2023::Day9::part2, 1068),
        entry(y2023::Day9::part2_math, 1068),
        entry(y2023::Day9::part2_sum, 1068),
        entry(y2023::Day10::part1, 7107),
        entry(y2023::Day10::part2, 281),
        entry(y2023::Day11::part1_old, 9627977),
        entry(y2023::Day11::part1_general, 9627977),
        entry(y2023::Day11::part1, 9627977),
        entry(y2023::Day11::part2_old, 644248339497),
        entry(y2023::Day11::part2_general, 644248339497),
        entry(y2023::Day11::part2, 644248339497),
        entry(y2023::Day12::part1, 6958),
        entry(y2023::Day12::part2, 6555315065024),
        entry(y2023::Day13::part1, 33780),
        entry(y2023::Day13::part2, 23479),
        entry(y2023::Day14::part1, 105461),
        entry(y2023::Day14::part2, 102829),
        entry(y2023::Day15::part1, 502139),
        entry(y2023::Day15::part2, 284132),
        entry(y2023::Day16::part1, 6883),
        entry(y2023::Day16::part2, 7228),
        entry(y2023::Day16::part2_precalc, 7228),
        entry(y2023::Day16::part2_bits, 7228),
        entry(y2023::Day17::part1, 1138),
        entry(y2023::Day17::part2, 1312),
        entry(y2023::Day18::part1, 48795),
        entry(y2023::Day18::part2, 40654918441248),
        entry(y2023::Day19::part1, 420739),
        entry(y2023::Day19::part2, 130251901420382),
        entry(y2023::Day20::part1, 883726240),
        entry(y2023::Day20::part1_cheat, 883726240),
        entry(y2023::Day20::part2, 211712400442661),
        entry(y2023::Day20::part2_cheat, 211712400442661),
        entry(y2023::Day21::part1, 3731),
        entry(y2023::Day21::part1_cheat, 3731),
        entry(y2023::Day21::part2, 617565692567199),
        entry(y2023::Day21::part2_cheat, 617565692567199),
        entry(y2023::Day22::part1, 443),
        entry(y2023::Day22::part2, 69915),
        entry(y2023::Day23::part1, 2010),
        entry(y2023::Day23::part2, 6318),
        entry(y2023::Day24::part1, 15107),
        entry(y2023::Day24::part2, 856642398547748),
        entry(y2023::Day25::part1, 544523),

        entry(y2024::Day1::part1, 1388114),
        entry(y2024::Day1::part2, 23529853),
        entry(y2024::Day2::part1, 252),
        entry(y2024::Day2::part2, 324),
        entry(y2024::Day3::part1, 159892596),
        entry(y2024::Day3::part2, 92626942),
        entry(y2024::Day4::part1, 2562),
        entry(y2024::Day4::part2, 1902),
        entry(y2024::Day5::part1, 5108),
        entry(y2024::Day5::part2, 7380),
        entry(y2024::Day6::part1, 5329),
        entry(y2024::Day6::part2, 2162),
        entry(y2024::Day7::part1, 2299996598890),
        entry(y2024::Day7::part2, 362646859298554),
        entry(y2024::Day8::part1, 371),
        entry(y2024::Day8::part2, 1229),
        entry(y2024::Day9::part1, 6463499258318),
        entry(y2024::Day9::part2, 6493634986625),
    };

    printf("      min │      max │   median │     mean │ name\n");
    printf("──────────┼──────────┼──────────┼──────────┼───────────\n");

    for (auto&& i : idk) {
        auto res = i.func();
        if (res != i.expected) {
            printf("%s incorrect solution %lu != %lu\n", i.name, res, i.expected);
        }

        auto [mean, times] = test(i.func);

        std::sort(times.begin(), times.end());
        auto med = median<decltype(times)::value_type>(times);

        std::cout << formatTime(times[0]) << " │"
                  << formatTime(times[times.size() - 1]) << " │"
                  << formatTime(med) << " │"
                  << formatTime(mean) << " │ "
                  << i.name << std::endl;
    }

    return 0;
}
