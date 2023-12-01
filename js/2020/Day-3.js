import { getInput } from "../util.js";
const input = getInput();

function countSlope(dx, dy) {
    let x = 0;
    let y = 0;

    let trees = 0;
    while (y < input.length) {
        if (input[y].charAt(x % 31) == "#") trees++;
        x += dx;
        y += dy;
    }
    return trees;
}

export function part1() {
    return countSlope(3, 1);
}

export function part2() {
    return countSlope(1, 1) * countSlope(3, 1) * countSlope(5, 1) * countSlope(7, 1) * countSlope(1, 2);
}

import { checkAnswers } from "../test.js";
checkAnswers();
