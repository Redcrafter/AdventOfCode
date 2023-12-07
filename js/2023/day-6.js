import { extractNumbers, getInput } from "../util.js";

const input1 = extractNumbers(getInput());
const input2 = extractNumbers(getInput().map(x => x.replace(/ /g, "")));

function solve(time, dist) {
    return 2 * Math.floor(Math.sqrt(time * time / 4 - dist - 1) + time / 2) + 1 - time;
}

export function part1() {
    let result = 1;

    for (let i = 0; i < input1[0].length; i++) {
        let time = input1[0][i];
        let dist = input1[1][i];

        result *= solve(time, dist);
    }

    return result;
}

export function part2() {
    let time = input2[0][0];
    let dist = input2[1][0];

    return solve(time, dist);
}

import { checkAnswers } from "../test.js";
checkAnswers();
