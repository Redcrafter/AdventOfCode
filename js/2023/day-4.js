import { extractNumbers, getInput } from "../util.ts";


/** @type {number[][]} */
const input = extractNumbers(getInput());

function countMatch(line) {
    let n = 0;
    for (let j = 11; j < line.length; j++) {
        const item = line[j];
        for (let k = 1; k < 11; k++) {
            if (item == line[k]) {
                n++;
                break;
            }
        }
    }
    return n;
}

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        let n = countMatch(line);
        result += (1 << n) >> 1;
    }

    return result;
}

export function part2() {
    let result = 0;

    let copies = new Uint32Array(256).fill(1);

    for (let i = 0; i < input.length; i++) {
        const line = input[i];
        const id = line[0];

        let n = countMatch(line);
        const count = copies[id - 1];
        for (let j = 0; j < n; j++) {
            copies[id + j] += count;
        }
        result += count;
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
