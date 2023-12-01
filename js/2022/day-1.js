import { getInput, arraySplit, sum } from "../util.js";
const input = arraySplit(getInput(false).map(x => x == "" ? "" : parseInt(x)), x => x == "");

export function part1() {
    // return Math.max(...input.map(x => sum(x)));

    let max = 0;

    for (let i = 0; i < input.length; i++) {
        const group = input[i];

        let sum = 0;
        for (let i = 0; i < group.length; i++) {
            sum += group[i];
        }
        max = Math.max(max, sum);
    }

    return max;
}

export function part2() {
    // return sum(input.map(x => sum(x)).sort((a, b) => b - a).slice(0, 3));

    let a = 0;
    let b = 0;
    let c = 0;

    for (let i = 0; i < input.length; i++) {
        const group = input[i];

        let sum = 0;
        for (let i = 0; i < group.length; i++) {
            sum += group[i];
        }

        if(sum > a) {
            c = b;
            b = a;
            a = sum;
        } else if(sum > b) {
            c = b;
            b = sum;
        } else if(sum > c) {
            c = sum;
        }
    }

    return a + b + c;
}

import { checkAnswers } from "../test.js";
checkAnswers();
