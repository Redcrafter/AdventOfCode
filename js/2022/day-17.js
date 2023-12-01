import { getInput } from "../util.js";

const input = getInput()[0];

const bitShapes = [
    0b0011110_0000000_0000000_0000000, // -
    0b0001000_0011100_0001000_0000000, // +
    0b0011100_0000100_0000100_0000000, // L
    0b0010000_0010000_0010000_0010000, // i
    0b0011000_0011000_0000000_0000000, // o
];

export function part1() {
    let grid = new Uint8Array(10000);
    let maxY = 0;
    let inputC = 0;

    for (let i = 0; i < 2022; i++) {
        let y = maxY + 3;
        let block = bitShapes[i % 5];

        while (true) {
            let row = (grid[y] << 21) | (grid[y + 1] << 14) | (grid[y + 2] << 7) | grid[y + 3];

            if (input[inputC % input.length] == "<") {
                if (!(block & 0b1000000_1000000_1000000_1000000 || row & (block << 1))) {
                    block <<= 1;
                }
            } else {
                if (!(block & 0b0000001_0000001_0000001_0000001 || row & (block >> 1))) {
                    block >>= 1;
                }
            }
            inputC++;

            if (y == 0 || ((grid[y - 1] << 21) | (grid[y] << 14) | (grid[y + 1] << 7) | grid[y + 2]) & block) {
                break;
            } else {
                y--;
            }
        }

        for (let i = 0; i < 4; i++) {
            grid[y + i] |= (block >> 21) & 0b1111111;
            if ((block >> 21) & 0b1111111) {
                maxY = Math.max(maxY, y + i + 1);
            }
            block <<= 7;
        }
    }

    return maxY;
}

export function part2() {
    let grid = new Uint8Array(10000);
    let maxY = 0;
    let inputC = 0;

    let extraY = 0;
    let seen = new Map();

    const cycles = 1000000000000;

    for (let i = 0; i < cycles; i++) {
        let y = maxY + 3;
        let block = bitShapes[i % 5];

        while (true) {
            let asd = (grid[y] << 21) | (grid[y + 1] << 14) | (grid[y + 2] << 7) | grid[y + 3];

            if (input[inputC % input.length] == "<") {
                if (!(block & 0b1000000_1000000_1000000_1000000 || asd & (block << 1))) {
                    block <<= 1;
                }
            } else {
                if (!(block & 0b0000001_0000001_0000001_0000001 || asd & (block >> 1))) {
                    block >>= 1;
                }
            }
            inputC++;

            if (y == 0 || ((grid[y - 1] << 21) | (grid[y] << 14) | (grid[y + 1] << 7) | grid[y + 2]) & block) {
                break;
            } else {
                y--;
            }
        }

        for (let i = 0; i < 4; i++) {
            grid[y + i] |= (block >> 21) & 0b1111111;
            if ((block >> 21) & 0b1111111) {
                maxY = Math.max(maxY, y + i + 1);
            }
            block <<= 7;
        }

        let key = inputC % input.length + ((i % 5) + grid[maxY - 1] * 5) * input.length;
        if (seen.has(key)) {
            let v = seen.get(key);

            let lines = maxY - v[0];
            let dt = i - v[1];

            let left = Math.floor((cycles - i) / dt);
            extraY += left * lines;
            i += left * dt;
        }
        seen.set(key, [maxY, i]);
    }

    return maxY + extraY;
}

import { checkAnswers } from "../test.js";
checkAnswers();
