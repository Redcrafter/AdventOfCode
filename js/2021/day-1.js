import { getInput } from "../util.ts";
const input = getInput().map(x => parseInt(x));

export function part1() {
    let count = 0;
    for (let i = 1; i < input.length; i++) {
        count += input[i] > input[i - 1];
    }
    return count;
}

export function part2() {
    let count = 0;
    for (let i = 3; i < input.length; i++) {
        let last = input[i - 3] + input[i - 2] + input[i - 1];
        let current = input[i - 2] + input[i - 1] + input[i];
        count += current > last;
    }
    return count;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
