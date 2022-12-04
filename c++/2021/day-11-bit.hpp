#pragma once
#include <array>
#include <bit>

namespace Day11_bit {

using uint128_t = unsigned __int128;
using Board = uint128_t;
using State = std::array<Board, 10>;

constexpr uint128_t rep10(uint128_t mask) {
    return mask | (mask << 10) | (mask << 20) | (mask << 30) | (mask << 40) | (mask << 50) | (mask << 60) | (mask << 70) | (mask << 80) | (mask << 90);
}

inline Board rotr(Board b) { return (b >> 1) & rep10(0b01111'11111); }
inline Board rotl(Board b) { return (b << 1) & rep10(0b11111'11110); }
inline Board rotd(Board b) { return b >> 10; }
inline Board rotu(Board b) { return (b << 10) & rep10(0b11111'11111); }

inline size_t count(Board b) {
    return std::popcount((uint64_t)b) + std::popcount((uint64_t)(b >> 64));
}

void prop(State& s, Board flash, Board& total_flash);

void bubble(State& s, Board flash, Board& total_flash) {
    Board to_up = 0;
    for (size_t i = 1; i < 10; i++) {
        s[i] |= to_up;
        to_up = s[i] & flash;
        s[i] &= ~to_up;
        flash &= ~to_up;
    }
    to_up &= ~total_flash;
    total_flash |= to_up;

    if (to_up != 0) prop(s, to_up, total_flash);
}

void prop(State& s, Board flash, Board& total_flash) {
    bubble(s, rotr(flash), total_flash);
    bubble(s, rotl(flash), total_flash);
    bubble(s, rotd(flash), total_flash);
    bubble(s, rotu(flash), total_flash);
    bubble(s, rotr(rotd(flash)), total_flash);
    bubble(s, rotl(rotd(flash)), total_flash);
    bubble(s, rotr(rotu(flash)), total_flash);
    bubble(s, rotl(rotu(flash)), total_flash);
}

State parseInput() {
    State result{0};

    auto input = readLines("../data/2021/day11.txt");

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++)
            result[input[i][j] - '0'] |= uint128_t(1) << (i * 10 + j);
    }

    return result;
}

const auto input = parseInput();

uint64_t part1() {
    auto s = input;

    size_t flash_count = 0;
    for (size_t i = 0; i < 100; i++) {
        Board flash = s[9];
        for (size_t i = 9; i > 0; i--) s[i] = s[i - 1];
        s[0] = 0;

        Board total_flash = flash;
        prop(s, flash, total_flash);
        s[0] = total_flash;
        flash_count += count(total_flash);
    }
    return flash_count;
}

uint64_t part2() {
    auto s = input;

    for (size_t i = 0;; i++) {
        Board flash = s[9];
        for (size_t i = 9; i > 0; i--) s[i] = s[i - 1];
        s[0] = 0;

        Board total_flash = flash;
        prop(s, flash, total_flash);
        s[0] = total_flash;

        if (total_flash == rep10(0b11111'11111)) {
            return i + 1;
        }
    }
}

}  // namespace Day11_bit
