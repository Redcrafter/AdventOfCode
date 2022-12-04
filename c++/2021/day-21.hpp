#pragma once
#include <array>
#include <cstdint>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <vector>

namespace Day21 {

const int player1 = 2;
const int player2 = 5;

uint64_t part1() {
    int p1 = player1 - 1;
    int p1Points = 0;

    int p2 = player2 - 1;
    int p2Points = 0;

    int dice = 0;
    int rolls = 0;

    auto roll = [&]() {
        int val = dice + 1;
        dice = val % 100;
        rolls++;
        return val;
    };
    auto roll3 = [&]() {
        return roll() + roll() + roll();
    };

    while (true) {
        p1 = (p1 + roll3()) % 10;
        p1Points += p1 + 1;
        if (p1Points >= 1000) break;

        p2 = (p2 + roll3()) % 10;
        p2Points += p2 + 1;
        if (p2Points >= 1000) break;
    }

    return std::min(p1Points, p2Points) * rolls;
}

struct Player {
    int position = 0;
    int points = 0;

    inline void step(int roll) {
        position = (position + roll) % 10;
        points += position + 1;
    }
};

struct State {
    Player p1{};
    Player p2{};
    uint64_t count;
    int turn = 0;

    inline void next(int roll) {
        if (turn == 0) {
            p1.step(roll);
        } else {
            p2.step(roll);
        }
        turn = !turn;
    }
};

const std::pair<uint64_t, uint64_t> rolls[] = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

uint64_t part2() {
    State s0{};
    s0.p1.position = player1 - 1;
    s0.p2.position = player2 - 1;
    s0.count = 1;

    std::vector<State> stack{};
    stack.emplace_back(s0);

    uint64_t p1Win = 0;
    uint64_t p2Win = 0;
    while (stack.size() > 0) {
        State el = stack[stack.size() - 1];
        stack.pop_back();

        for (auto &&i : rolls) {
            State next = el;
            next.next(i.first);

            next.count *= i.second;

            if (next.p1.points >= 21) {
                p1Win += next.count;
            } else if (next.p2.points >= 21) {
                p2Win += next.count;
            } else {
                stack.emplace_back(next);
            }
        }
    }

    return std::max(p1Win, p2Win);
}

}  // namespace Day21
