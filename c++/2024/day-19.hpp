#pragma once
#include <ranges>
#include <unordered_map>

#include "../aoc.hpp"
#include "../util.hpp"

namespace y2024::Day19 {

auto toStringView(std::ranges::subrange<const char*>&& r) {
    return std::string_view(r.begin(), r.size());
}

auto parse() {
    const auto input = aoc::getInput(2024, 19);
    auto split_ = input.find('\n');

    using std::operator""sv;

    std::vector<std::string_view> patterns;
    for(auto&& el : input.substr(0, split_) | std::views::split(", "sv)) {
        patterns.push_back(std::string_view(el.begin(), el.size()));
    }
    auto items = split(input.substr(split_ + 2), '\n');

    return std::pair(patterns, items);
}
const auto [input1, input2] = parse();

bool starts_with(std::string_view a, std::string_view b) {
    if(a.size() < b.size()) return false;
    for(int i = 0; i < b.size(); i++) {
        if(a[i] != b[i]) return false;
    }
    return true;
}

bool testDesign(std::string_view str) {
    if(str.size() == 0) return true;

    for(auto el : input1) {
        if(starts_with(str, el)) {
            if(testDesign(str.substr(el.size()))) {
                return true;
            }
        }
    }

    return false;
}

uint64_t part1() {
    uint64_t res = 0;
    for(auto line : input2) {
        if(testDesign(line)) {
            res++;
        }
    }
    return res;
}

uint64_t testDesign2(std::string_view str, std::unordered_map<std::string_view, uint64_t>& known) {
    if(str.size() == 0) return 1;

    auto& el = known[str];
    if(el != 0)
        return el;

    uint64_t res = 0;
    for(auto el : input1) {
        if(starts_with(str, el)) {
            res += testDesign2(str.substr(el.size()), known);
        }
    }

    el = res;
    return res;
}

uint64_t part2() {
    std::unordered_map<std::string_view, uint64_t> known;

    uint64_t res = 0;
    for(auto line : input2) {
        res += testDesign2(line, known);
    }
    return res;
}

static auto p = aoc::test([]() { return parse().first.size(); }, 2024, 19, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 19, 1, "part 1");
static auto p2 = aoc::test(part2, 2024, 19, 2, "part 2");

} // namespace y2024::Day19
