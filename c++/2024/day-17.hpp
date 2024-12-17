#pragma once
#include <span>

#include "../aoc.hpp"
#include "../fixedVector.hpp"
#include "../util.hpp"

namespace y2024::Day17 {

auto parse() {
    auto nums = extractNumbers<uint32_t>(aoc::getInput(2024, 17));
    std::array<uint32_t, 16> prog;
    for(size_t i = 0; i < prog.size(); i++) {
        prog[i] = nums[i + 3];
    }

    return std::pair(nums[0], prog);
}
const auto [a, program] = parse();

auto run(fixedVector<uint32_t, 32>& out, uint64_t a) {
    uint64_t b = 0;
    uint64_t c = 0;
    int pc = 0;

    auto combo = [&](int i) {
        switch(i) {
            case 0: return (uint64_t)0;
            case 1: return (uint64_t)1;
            case 2: return (uint64_t)2;
            case 3: return (uint64_t)3;
            case 4: return a;
            case 5: return b;
            case 6: return c;
            default: std::unreachable();
        }
    };

    while(pc < program.size()) {
        auto op = program[pc];
        auto param = program[pc + 1];

        switch(op) {
            case 0: a = (a / (1 << combo(param))); break;
            case 1: b = b ^ param; break;
            case 2: b = combo(param) % 8; break;
            case 3:
                if(a != 0) {
                    pc = param;
                    continue;
                }
                break;
            case 4: b = b ^ c; break;
            case 5: out.push_back(combo(param) % 8); break;
            case 6: b = (a / (1 << combo(param))); break;
            case 7: c = (a / (1 << combo(param))); break;
        }

        pc += 2;
    }
}

std::string part1() {
    fixedVector<uint32_t, 32> result{};

    run(result, a);

    std::string res;
    for(size_t i = 0; i < result.size(); i++) {
        if(i != 0) res += ",";
        res += std::to_string(result[i]);
    }
    return res;
}

uint64_t findA(uint64_t a, fixedVector<uint32_t, 32>& res) {
    for(int i = 0; i < 8; i++) {
        res.clear();
        run(res, a * 8 + i);
        if(res.size() == 0) continue;

        if(res[0] == program[program.size() - res.size()]) {
            if(res.size() == program.size()) {
                return a * 8 + i;
            }
            auto r = findA(a * 8 + i, res);
            if(r != 0) return r;
        }
    }
    return 0;
}

uint64_t part2() {
    fixedVector<uint32_t, 32> res;
    return findA(0, res);
}

uint64_t part2_flat() {
    fixedVector<uint32_t, 32> res;

    uint64_t a = 0;
    while(true) {
        res.clear();
        run(res, a);

        if(res[0] == program[program.size() - res.size()]) {
            if(res.size() == program.size()) {
                return a;
            }
            a <<= 3;
            continue;
        }
        while((a & 7) == 7) {
            a >>= 3;
        }
        a++;
    }
}

uint64_t part2_caavik() {
    auto prog = program;
    int operand1 = program[3];
    int operand2 = program[6] == 1 ? program[7] : program[8] == 1 ? program[9] : program[11];

    for(int i = 0; i < 16; i++)
        prog[i] ^= operand2;

    int digit = 15;
    int curDigit = prog[digit];
    int64_t a = 0;

    while(true) {
        int b = (a & 7) ^ operand1;
        if((b ^ ((a >> b) & 7)) == curDigit) {
            if(digit == 0) {
                return a;
            }

            a <<= 3;
            digit--;
            curDigit = prog[digit];
            continue;
        }

        if((a & 7) == 7) {
            do {
                a >>= 3;
                digit++;
            } while((a & 7) == 7);
            curDigit = prog[digit];
        }
        a++;
    }
}

static auto p = aoc::test([]() { return (uint64_t)parse().first; }, 2024, 17, 0, "parse");
static auto p1 = aoc::test(part1, 2024, 17, 1, "part 1");
static auto p2r = aoc::test(part2, 2024, 17, 2, "part 2 recursive");
static auto p2f = aoc::test(part2_flat, 2024, 17, 2, "part 2 flat");
static auto p2c = aoc::test(part2_caavik, 2024, 17, 2, "part 2 caavik");

} // namespace y2024::Day17
