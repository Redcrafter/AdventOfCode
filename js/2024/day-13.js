import { extractNumbers, getInput } from "../util.ts";

const input = extractNumbers(getInput());

function calc(a, b, p) {
    const det = a[0] * b[1] - b[0] * a[1];

    const ac = (p[0] * b[1] - p[1] * b[0]) / det;
    const bc = (p[1] * a[0] - p[0] * a[1]) / det;

    if (ac != Math.floor(ac) || bc != Math.floor(bc)) return 0;
    return 3 * ac + bc;
}

export function part1() {
    let result = 0;
    for (let i = 0; i < input.length; i += 3) {
        result += calc(input[i], input[i + 1], input[i + 2]);
    }
    return result;
}

export function part2() {
    let result = 0;
    for (let i = 0; i < input.length; i += 3) {
        const e = input[i + 2];
        result += calc(input[i], input[i + 1], [e[0] + 10000000000000, e[1] + 10000000000000]);
    }
    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
