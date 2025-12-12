import { extractNumbers, getInput, sum } from "../util.ts";

const input = extractNumbers(getInput()[0]);

function solve(n) {
    let curr = new Map(input.map(x => [x, 1]));
    let next = new Map();
    function add(v, n) {
        next.set(v, (next.get(v) ?? 0) + n);
    }
    for (let i = 0; i < n; i++) {
        next.clear();

        for (const [s, count] of curr) {
            if (s == 0) {
                add(1, count);
            } else {
                let len = Math.floor(Math.log10(s) + 1);
                if (len % 2 == 0) {
                    len = (10 ** (len / 2));
                    add((s / len) | 0, count)
                    add(s % len, count)
                } else {
                    add(s * 2024, count);
                }
            }
        }
        [curr, next] = [next, curr];
    }
    return sum(curr.values());
}

export function part1() {
    return solve(25);
}

export function part2() {
    return solve(75);
}

import { checkAnswers } from "../test.ts";
checkAnswers();
