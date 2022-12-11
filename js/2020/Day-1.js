import { getInput } from "../util.js";
const input = getInput().map(x => parseInt(x));
input.sort((a, b) => a - b);

export function part1() {
    for (let i = 0; i < input.length; i++) {
        for (let j = 0; j < input.length; j++) {
            if (input[i] + input[j] == 2020) {
                return input[i] * input[j];
            }
        }
    }
}

export function part2() {
    for (let i = 0; i < input.length; i++) {
        for (let j = 0; j < input.length; j++) {
            for (let k = 0; k < input.length; k++) {
                if (input[i] + input[j] + input[k] == 2020) {
                    return input[i] * input[j] * input[k];
                }
            }
        }
    }
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
