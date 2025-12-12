import { extractNumbers, getInput, sum } from "../util.ts";

const input = extractNumbers(getInput(false).slice(30, -1));

export function part1() {
    return input.reduce((c, line) => c + (Math.floor(line[0] / 3) * Math.floor(line[1] / 3) >= sum(line.slice(2))), 0);
}

export function part2() {
    return 0;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
