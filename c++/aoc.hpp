#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <variant>
#include <vector>

namespace aoc {

using numFunc = uint64_t (*)();
using stringFunc = std::string (*)();

struct RegisteredFunction {
    // std::source_location location;
    std::string name;
    int year;
    int day;
    int part;

    std::variant<numFunc, stringFunc> func;
};

auto& registered_functions() {
    static std::vector<RegisteredFunction> v;
    return v;
}

RegisteredFunction& test(uint64_t (*func)(), int year, int day, int part, const char* name) {
    auto& funs = registered_functions();
    funs.emplace_back(name, year, day, part, func);
    return funs.back();
}

RegisteredFunction& test(std::string (*func)(), int year, int day, int part, const char* name) {
    auto& funs = registered_functions();
    funs.emplace_back(name, year, day, part, func);
    return funs.back();
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::string res((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return res;
}

std::string_view getInput(int year, int day) {
    static std::array<std::string, 256> known;

    auto& v = known[(year - 2020) * 25 + day];
    if(v.empty()) {
        auto path = std::format("../data/{}/day{}.txt", year, day);
        if(!std::filesystem::exists(path)) {
            printf("Missing input file for %i day %i", year, day);
            exit(1);
        }
        known[(year - 2020) * 25 + day] = readFile(path);
    }
    return known[(year - 2020) * 25 + day];
}

} // namespace aoc
