import { getInput } from "../util.js";

const input = getInput().map(x => parseInt(x));

export function part1() {
    function check(i) {
        let val = input[i];

        for (let j = 0; j < 25; j++) {
            for (let k = j + 1; k < 25; k++) {
                if (input[i - 25 + j] + input[i - 25 + k] == val) {
                    return true;
                }
            }
        }

        return false;
    }

    for (let i = 25; i < input.length; i++) {
        if (!check(i)) {
            return input[i];
        }
    }
}

export function part2() {
    let val = part1();

    let start = 0;
    let end = 0;
    let s = 0;

    while (true) {
        if (s < val) {
            s += input[end];
            end++;
        }

        if (s == val)
            break;

        if (s > val) {
            s -= input[start];
            start++;
        }
    }

    let range = input.slice(start, end);
    return Math.min(...range) + Math.max(...range);
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
