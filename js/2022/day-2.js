import { getInput, sum } from "../util.js";
const input = getInput();

const A = "A".charCodeAt(0);
const X = "X".charCodeAt(0);

export function part1() {
    let res = 0;

    for (let i = 0; i < input.length; i++) {
        const a = input[i].charCodeAt(0) - A;
        const b = input[i].charCodeAt(2) - X;

        res += b + 1 + ((b - a + 4) % 3) * 3;
    }

    return res;
}

export function part2() {
    let res = 0;

    for (let i = 0; i < input.length; i++) {
        const a = input[i].charCodeAt(0) - A;
        const b = input[i].charCodeAt(2) - X;

        res += b * 3 + ((b + a + 2) % 3) + 1;
    }

    return res;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 12855);
    console.assert(part2() == 13726);
}
