import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput());

export function part1() {
    let result = 0;
    for (let i = 0; i < input.length; i++) {
        let num = input[i];
        for (let j = 0; j < 2000; j++) {
            num = (num ^ (num << 6)) & 0xFFFFFF;
            num = num ^ (num >> 5);
            num = num ^ (num << 11);
        }
        result += num & 0xFFFFFF;
    }
    return result;
}

export function part2() {
    const possible = new Uint16Array(1 << 20);
    const sub = new Uint8Array(1 << 20);
    sub.fill(255);
    const is = [];

    for (let i = 0; i < input.length; i++) {
        let num = input[i][0];
        let last = num;

        let seq = 0;

        for (let j = 0; j < 2000; j++) {
            num = num ^ ((num << 6) & 0xFFFFFF);
            num = num ^ ((num >> 5) & 0xFFFFFF);
            num = num ^ ((num << 11) & 0xFFFFFF);

            seq = (seq << 5) + (((num % 10) - (last % 10)) + 9);
            seq = seq & 0xFFFFF;

            if (j >= 3 && sub[seq] == 255) {
                is.push(seq);
                sub[seq] = num % 10;
            }
            last = num;
        }

        while (is.length > 0) {
            let i = is.pop();
            possible[i] += sub[i];
            sub[i] = 255;
        }
    }

    let result = 0;
    for (const val of possible) {
        result = Math.max(result, val);
    }
    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
