import { getInput } from "../util.js";

const input = getInput();
const input1 = input[0];
const input2 = input.slice(1);

export function part1() {
    const pad = 4;
    const width = input2[0].length + pad * 2;
    const height = input2.length + pad * 2;

    const map = new Uint8Array(input1.length);
    for (let i = 0; i < input1.length; i++) map[i] = input1.charCodeAt(i) == 35;

    let grid = new Uint8Array(width * height);
    let next = new Uint8Array(width * height);

    for (let y = 0; y < input2.length; y++) {
        let line = input2[y];
        for (let x = 0; x < line.length; x++) {
            grid[(x + pad) + (y + pad) * width] = line.charCodeAt(x) == 35;
        }
    }

    function step() {
        for (let i = width + 1; i < grid.length - width - 1; i++) {
            let num =
                grid[i - width - 1] << 8 | grid[i - width] << 7 | grid[i - width + 1] << 6 |
                grid[i         - 1] << 5 | grid[i        ] << 4 | grid[i         + 1] << 3 |
                grid[i + width - 1] << 2 | grid[i + width] << 1 | grid[i + width + 1] << 0;

            next[i] = map[num];
        }

        let inf = next[width + 1];
        for (let i = 0; i < width; i++) {
            next[i] = inf;
            next[i + (height - 1) * width] = inf;

            next[i * width] = inf;
            next[i * width + (width - 1)] = inf;
        }

        let temp = grid;
        grid = next;
        next = temp;
    }

    step();
    step();

    let count = 0;
    for (let i = 0; i < grid.length; i++) {
        count += grid[i];
    }
    return count;
}

export function part2() {
    const pad = 55;
    const width = input2[0].length + pad * 2;
    const height = input2.length + pad * 2;

    const map = new Uint8Array(input1.length);
    for (let i = 0; i < input1.length; i++) map[i] = input1.charCodeAt(i) == 35;

    let grid = new Uint8Array(width * height);
    let next = new Uint8Array(width * height);

    for (let y = 0; y < input2.length; y++) {
        let line = input2[y];
        for (let x = 0; x < line.length; x++) {
            grid[(x + 55) + (y + 55) * width] = line.charCodeAt(x) == 35;
        }
    }

    function step() {
        for (let i = width + 1; i < grid.length - width - 1; i++) {
            let num =
                grid[i - width - 1] << 8 | grid[i - width] << 7 | grid[i - width + 1] << 6 |
                grid[i         - 1] << 5 | grid[i        ] << 4 | grid[i         + 1] << 3 |
                grid[i + width - 1] << 2 | grid[i + width] << 1 | grid[i + width + 1] << 0;

            next[i] = map[num];
        }

        // fill in edges
        let inf = next[width + 1];
        for (let i = 0; i < width; i++) {
            next[i] = inf;
            next[i + (height - 1) * width] = inf;

            next[i * width] = inf;
            next[i * width + (width - 1)] = inf;
        }

        // swap buffers
        let temp = grid;
        grid = next;
        next = temp;
    }

    for (let i = 0; i < 50; i++) {
        step();
    }

    let count = 0;
    for (let i = 0; i < grid.length; i++) {
        count += grid[i];
    }
    return count;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
