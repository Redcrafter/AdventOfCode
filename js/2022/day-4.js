import { extractNumbers, getInput } from "../util.js";
const input = extractNumbers(getInput());

export function part1() {
    // return input.reduce((a, [x, y, z, w]) => a + ((x <= z && y >= w) || (z <= x && w >= y)), 0);
    let res = 0;

    for (const [x, y, z, w] of input) {
        if ((x <= z && y >= w) || (z <= x && w >= y)) res++;
    }

    return res;
}

export function part2() {
    // return input.reduce((a, [x, y, z, w]) => a + (x <= w && y >= z), 0);
    let res = 0;

    for (const [x1, y1, x2, y2] of input) {
        if (x1 <= y2 && y1 >= x2) res++;
    }

    return res;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.log(part1() == 595);
    console.log(part2() == 952);
}
