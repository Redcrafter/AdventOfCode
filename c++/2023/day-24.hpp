#pragma once
#include <array>
#include <bitset>

#include "../aoc.hpp"
#include "../util.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"

namespace y2023::Day24 {

const auto input = aoc::getInput(2023, 24);

struct El {
    vec3<int64_t> start;
    vec3<int32_t> vel;
};

auto parse() {
    std::vector<El> lines;
    lines.reserve(300);

    size_t pos = 0;
    while(pos < input.size()) {
        int64_t x = readUInt128(input, pos);
        pos++;
        int64_t y = readUInt128(input, pos);
        pos++;
        int64_t z = readUInt128(input, pos);
        pos += 2;

        auto vx = readSInt(input, pos);
        pos++;
        auto vy = readSInt(input, pos);
        pos++;
        auto vz = readSInt(input, pos);

        lines.push_back({{x, y, z}, {vx, vy, vz}});
    }

    return lines;
}

vec2<float> toSlope(vec3<int64_t> a, vec3<int32_t> v) {
    auto s = v.y / (float)v.x;
    return {a.y - (s * a.x), s};
}

// inputs are slopes p.x + p.y * x
vec2<float> intersect(vec2<float> p0, vec2<float> p1) {
    auto [c, a] = p0;
    auto [d, b] = p1;
    return {(d - c) / (a - b), a * (d - c) / (a - b) + c};
}

uint64_t part1() {
    auto lines = parse();
    uint64_t result = 0;

    const float min = 200000000000000.0f;
    const float max = 400000000000000.0f;

    for(size_t i = 0; i < lines.size(); i++) {
        auto a = lines[i];
        auto sa = toSlope(a.start, a.vel);

        for(size_t j = i + 1; j < lines.size(); j++) {
            auto b = lines[j];
            auto sb = toSlope(b.start, b.vel);

            auto [x, y] = intersect(sa, sb);

            if((x - a.start.x) / a.vel.x < 0 || (y - a.start.y) / a.vel.y < 0)
                continue;
            if((x - b.start.x) / b.vel.x < 0 || (y - b.start.y) / b.vel.y < 0)
                continue;
            if(x >= min && x <= max && y >= min && y <= max)
                result++;
        }
    }

    return result;
}

// curtesy to frankzig on the aoc discord
uint64_t part2() {
    auto nums = parse();

    auto A = nums[0];
    auto B = nums[1];
    auto C = nums[2];

    // The idea is bruteforcing over velocities, this turns a quadratic system
    // into a linear system that can be solved efficiently with a bit of algebra.
    // After guessing a set of velocities, here we solve the reduced linear system
    // and we check that it matches with 3 particles, if it does then it must be
    // the only solution.
    const auto LO_V = -300;
    const auto HI_V = 200; // the range is somewhat optimised to work both with inp and ex.
    auto a2 = B.start.x - A.start.x;
    auto b2 = B.start.y - A.start.y;

    for(int64_t vx = LO_V; vx <= HI_V; vx++) {
        auto a0 = -(vx - A.vel.x);
        auto a1 = vx - B.vel.x;

        for(int64_t vy = LO_V; vy <= HI_V; vy++) {
            auto b0 = A.vel.y - vy;
            auto b1 = vy - B.vel.y;
            auto det = a1 * b0 - a0 * b1;
            if(det == 0)
                continue;

            auto t1 = (a1 * b2 - a2 * b1) / det;
            auto t2 = (a2 * b0 - a0 * b2) / det;
            if(t1 < 0 || t2 < 0)
                continue;

            auto px = A.start.x - t1 * (vx - A.vel.x);
            auto py = A.start.y - t1 * (vy - A.vel.y);
            if(px + t1 * vx != A.start.x + t1 * A.vel.x ||
               py + t1 * vy != A.start.y + t1 * A.vel.y ||
               px + t2 * vx != B.start.x + t2 * B.vel.x ||
               py + t2 * vy != B.start.y + t2 * B.vel.y) {
                continue;
            }

            for(int64_t vz = LO_V; vz <= HI_V; vz++) {
                auto pz = A.start.z - t1 * (vz - A.vel.z);

                int64_t t3 = -1;
                if((vx - C.vel.x) != 0) {
                    t3 = (C.start.x - px) / (vx - C.vel.x);
                } else if((vy - C.vel.y) != 0) {
                    t3 = (C.start.y - py) / (vy - C.vel.y);
                } else if((vz - C.vel.z) != 0) {
                    t3 = (C.start.z - pz) / (vz - C.vel.z);
                }

                if(t3 >= 0 &&
                   pz + t1 * vz == A.start.z + t1 * A.vel.z &&
                   pz + t2 * vz == B.start.z + t2 * B.vel.z &&
                   px + t3 * vx == C.start.x + t3 * C.vel.x &&
                   py + t3 * vy == C.start.y + t3 * C.vel.y &&
                   pz + t3 * vz == C.start.z + t3 * C.vel.z) {
                    return px + py + pz;
                }
            }
        }
    }

    printf("Solution not found. increase bruteforce velocity set\n");
    return 0;
}

static auto p1 = aoc::test(part1, 2023, 24, 1, "part1");
static auto p2 = aoc::test(part2, 2023, 24, 2, "part2");

} // namespace y2023::Day24
