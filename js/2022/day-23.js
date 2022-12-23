import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    const h = Math.floor(input.length / 2);

    const size = input.length * 2;
    const sh = input.length;
    const grid = new Uint8Array(size * size);

    function get(x, y) {
        return grid[x + y * size];
    }

    const elves = [];

    for (let y = 0; y < input.length; y++) {
        let line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line[x] == "#") {
                grid[(x + sh - h) + (y + sh - h) * size] = 1;
                elves.push([x + sh - h, y + sh - h]);
            }
        }
    }

    const funcs = [
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!N && !NE && !NW) ? x + (y - 1) * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!S && !SE && !SW) ? x + (y + 1) * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!W && !NW && !SW) ? (x - 1) + y * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!E && !NE && !SE) ? (x + 1) + y * size : 0,
    ];

    const dirs = new Uint32Array(elves.length);
    const consider = new Uint8Array(size * size);

    let minX = Infinity;
    let maxX = 0;
    let minY = Infinity;
    let maxY = 0;

    for (let i = 0; i < 10; i++) {
        for (let k = 0; k < elves.length; k++) {
            const [x, y] = elves[k];

            const NW = get(x - 1, y - 1);
            const N = get(x, y - 1);
            const NE = get(x + 1, y - 1);
            const W = get(x - 1, y);
            const E = get(x + 1, y);
            const SW = get(x - 1, y + 1);
            const S = get(x, y + 1);
            const SE = get(x + 1, y + 1);

            dirs[k] = 0;
            if (NW + N + NE + W + E + SW + S + SE != 0) {
                for (let j = 0; j < 4; j++) {
                    let key = funcs[(j + i) % 4](x, y, NW, N, NE, W, E, SW, S, SE);
                    if (key) {
                        consider[key]++;
                        dirs[k] = key;
                        break;
                    }
                }
            }
        }

        for (let k = 0; k < elves.length; k++) {
            const [x, y] = elves[k];
            const dir = dirs[k];

            if (dir != 0 && consider[dir] == 1) {
                grid[x + y * size] = 0;
                grid[dir] = 1;

                const dx = dir % size;
                const dy = Math.floor(dir / size);

                elves[k][0] = dx;
                elves[k][1] = dy;

                minX = Math.min(minX, dx);
                maxX = Math.max(maxX, dx);
                minY = Math.min(minY, dy);
                maxY = Math.max(maxY, dy);
            }
            consider[dir] = 0;
        }
    }

    return (maxX - minX + 1) * (maxY - minY + 1) - elves.length;
}

export function part2() {
    const size = input.length * 3;
    const sh = Math.floor(size / 2);

    const grid = new Uint8Array(size * size);
    const h = Math.floor(input.length / 2);

    function get(x, y) {
        return grid[x + y * size];
    }

    const elves = [];

    for (let y = 0; y < input.length; y++) {
        const line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line[x] == "#") {
                grid[(x + sh - h) + (y + sh - h) * size] = 1;
                elves.push([x + sh - h, y + sh - h]);
            }
        }
    }

    const funcs = [
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!N && !NE && !NW) ? x + (y - 1) * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!S && !SE && !SW) ? x + (y + 1) * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!W && !NW && !SW) ? (x - 1) + y * size : 0,
        (x, y, NW, N, NE, W, E, SW, S, SE) => (!E && !NE && !SE) ? (x + 1) + y * size : 0,
    ];

    const dirs = new Uint32Array(elves.length);
    const consider = new Uint8Array(size * size);

    let i = 0;
    while (true) {
        for (let k = 0; k < elves.length; k++) {
            const [x, y] = elves[k];

            const NW = get(x - 1, y - 1);
            const N = get(x, y - 1);
            const NE = get(x + 1, y - 1);
            const W = get(x - 1, y);
            const E = get(x + 1, y);
            const SW = get(x - 1, y + 1);
            const S = get(x, y + 1);
            const SE = get(x + 1, y + 1);

            dirs[k] = 0;
            if (NW + N + NE + W + E + SW + S + SE != 0) {
                for (let j = 0; j < 4; j++) {
                    const key = funcs[(j + i) % 4](x, y, NW, N, NE, W, E, SW, S, SE);
                    if (key) {
                        consider[key]++;
                        dirs[k] = key;
                        break;
                    }
                }
            }
        }

        let moved = false;
        for (let k = 0; k < elves.length; k++) {
            const [x, y] = elves[k];
            const dir = dirs[k];

            if (dir != 0 && consider[dir] == 1) {
                grid[x + y * size] = 0;
                grid[dir] = 1;

                elves[k][0] = dir % size;
                elves[k][1] = Math.floor(dir / size);
                moved = true;
            }
            consider[dir] = 0;
        }

        i++;
        if (!moved) {
            break;
        }
    }

    return i;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
