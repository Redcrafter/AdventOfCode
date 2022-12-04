import { getInput } from "../util.js";
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

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 1226);
    console.assert(part2() == 1252);
}
