import { getInput } from "../util.ts";

const input = getInput();

export function part1() {
    const height = input.length;
    const width = input[0].length;
    let grid = new Uint8Array(width * height);
    let next = new Uint8Array(width * height);

    for (let y = 0; y < height; y++) {
        const line = input[y];
        for (let x = 0; x < width; x++) {
            let char = line[x];
            if (char == '>') grid[x + y * width] = 1;
            if (char == 'v') grid[x + y * width] = 2;
        }
    }

    let i = 0;
    while (true) {
        let changed = false;

        next.fill(0);
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                let idx = x + y * width;
                let n = (x + 1) % width + y * width;

                if (grid[idx] == 1 && grid[n] == 0) {
                    next[n] = 1;
                    changed = true;
                } else if (grid[idx]) {
                    next[idx] = grid[idx];
                }
            }
        }

        let temp = grid;
        grid = next;
        next = temp;

        next.fill(0);
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                let idx = x + y * width;
                let n = x + ((y + 1) % height) * width;

                if (grid[idx] == 2 && grid[n] == 0) {
                    next[n] = 2;
                    changed = true;
                } else if (grid[idx]) {
                    next[idx] = grid[idx];
                }
            }
        }

        temp = grid;
        grid = next;
        next = temp;

        i++;

        if (!changed) break;
    }

    return i;
}

export function part2() {
    return null;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
