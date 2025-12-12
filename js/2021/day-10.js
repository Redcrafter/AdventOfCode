import { getInput } from "../util.ts";
const input = getInput();

export function part1() {
    function check(line) {
        let stack = [];

        for (let i = 0; i < line.length; i++) {
            const c = line.charCodeAt(i);

            switch (c) {
                case 40: // (
                case 91: // [
                case 123: // {
                case 60: // <
                    stack.push(c); break;

                case 41: // )
                    if (stack.pop() != 40) return 3;
                    break;
                case 93: // ]
                    if (stack.pop() != 91) return 57;
                    break;
                case 125: // }
                    if (stack.pop() != 123) return 1197;
                    break;
                case 62: // >
                    if (stack.pop() != 60) return 25137;
                    break;
            }
        }

        return 0;
    }

    let sum = 0;
    for (const line of input) {
        sum += check(line);
    }
    return sum;
}

export function part2() {
    function check(line) {
        let stack = [];

        for (let i = 0; i < line.length; i++) {
            const c = line.charCodeAt(i);

            switch (c) {
                case 40: // (
                case 91: // [
                case 123: // {
                case 60: // <
                    stack.push(c); break;

                case 41: // )
                    if (stack.pop() != 40) return 0;
                    break;
                case 93: // ]
                    if (stack.pop() != 91) return 0;
                    break;
                case 125: // }
                    if (stack.pop() != 123) return 0;
                    break;
                case 62: // >
                    if (stack.pop() != 60) return 0;
                    break;
            }
        }

        let score = 0;
        for (let i = stack.length - 1; i >= 0; i--) {
            const v = stack[i];
            score *= 5;
            if (v == 40) score += 1;
            if (v == 91) score += 2;
            if (v == 123) score += 3;
            if (v == 60) score += 4;
        }
        return score;
    }

    let sums = [];
    for (const line of input) {
        let val = check(line);
        if (val != 0) sums.push(val);
    }
    sums.sort((a, b) => a - b);

    return sums[Math.floor(sums.length / 2)];
}

import { checkAnswers } from "../test.ts";
checkAnswers();
