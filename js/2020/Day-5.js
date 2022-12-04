import { getInput } from "../util.js";
const input = getInput()

let grid = [];
for (let i = 0; i < 128; i++) {
    grid[i] = new Array(8).fill(0);
}

let max = 0;
let min = Infinity;
for (const l of input) {
    let x = 0;

    let num = 64;
    for (let i = 0; i < 7; i++) {
        if (l[i] == "B") x += num;

        num /= 2;
    }

    let y = 0;
    num = 4;
    for (let i = 0; i < 3; i++) {
        if (l[i + 7] == "R") y += num;

        num /= 2;
    }

    grid[x][y] = 1;
    max = Math.max(max, x);
    min = Math.min(min, x);
}

export function part1() {
    for (let x = max; x >= min; x--) {
        for (let y = 7; y >= 0; y--) {
            if (grid[x][y] == 1)
                return x * 8 + y;
        }
    }
}

export function part2() {
    for (let x = min + 1; x < max; x++) {
        for (let y = 0; y < 8; y++) {
            if (grid[x][y] != 1)
                return x * 8 + y;
        }
    }

}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 906)
    console.assert(part2() == 519)
}
