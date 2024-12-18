#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <span>
#include <tuple>
#include <vector>

#include "days.hpp"
#include "json.hpp"

template<class T>
inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

template<class T>
inline void DoNotOptimize(T& value) {
#if defined(__clang__)
    asm volatile("" : "+r,m"(value) : : "memory");
#else
    asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

template<typename R>
auto test(R(func)()) {
    std::chrono::nanoseconds time{};
    std::vector<std::chrono::duration<double, std::nano>> times;

    // time 1 run to determine loop count
    auto start = std::chrono::high_resolution_clock::now();
    auto val = func();
    DoNotOptimize(val);
    auto end = std::chrono::high_resolution_clock::now();

    // make it so 1 sample step takes ~10ms
    const auto runs = std::ceil((10 * 1000 * 1000.0) / (end - start).count());

    int i = 0;
    while(time < std::chrono::seconds(10)) {
        auto start = std::chrono::high_resolution_clock::now();

        for(size_t i = 0; i < runs; i++) {
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

template<typename T>
auto median(const std::span<T>& arr) {
    auto mid = arr.size() / 2;
    if(arr.size() % 2 == 0) {
        return (arr[mid - 1] + arr[mid]) / 2;
    } else {
        return arr[mid];
    }
}

std::string formatTime(std::chrono::duration<double, std::nano> value) {
    // clang does not support std::format yet. come on
    char buf[256];
    if(value < std::chrono::microseconds(1)) {
        sprintf(buf, "%7.2fns", value.count());
    } else if(value < std::chrono::milliseconds(1)) {
        sprintf(buf, "%7.2fμs", value.count() / 1e3);
    } else if(value < std::chrono::seconds(1)) {
        sprintf(buf, "%7.2fms", value.count() / 1e6);
    } else {
        sprintf(buf, "%7.2fs ", value.count() / 1e9);
    }
    return buf;
}

template<typename T>
void runFunc(aoc::RegisteredFunction& i, std::chrono::duration<double, std::nano>& total, nlohmann::json& solutions) {
    auto fp = std::get<T (*)()>(i.func);

    if(i.part != 0) {
        auto res = fp();
        T expected = solutions[std::to_string(i.year)][std::to_string(i.day)][i.part - 1];
        if(res != expected) {
            std::cout << i.year << "-" << i.day << "-" << i.name << " incorrect solution " << res << " != " << expected << std::endl;
            // printf("{}-{}-{} incorrect solution {} != {}\n", i.year, i.day, i.name.c_str(), res, expected);
            return;
        }
    }

    auto [mean, times] = test(fp);

    total += mean;

    std::sort(times.begin(), times.end());
    auto med = median(std::span(times));

    // drawGraph(times, mean);

    std::cout << " " << i.year << "-" << std::format("{:02}", i.day) << " │"
              << formatTime(times[0]) << " │"
              << formatTime(times[times.size() - 1]) << " │"
              << formatTime(med) << " │"
              << formatTime(mean) << " │ "
              << i.name << std::endl;
}

int main() {
    std::ifstream f("../data/solutions.json");
    auto solutions = nlohmann::json::parse(f);

    printf("   day   │      min │      max │   median │     mean │ name\n");
    printf("─────────┼──────────┼──────────┼──────────┼──────────┼───────────\n");

    std::chrono::duration<double, std::nano> total{0};

    auto funs = aoc::registered_functions();
    for(auto&& i : funs) {
        if(std::holds_alternative<aoc::numFunc>(i.func)) {
            runFunc<uint64_t>(i, total, solutions);
        } else {
            runFunc<std::string>(i, total, solutions);
        }
    }

    std::cout << "Total time:" << formatTime(total) << std::endl;

    return 0;
}
