import { getInput } from "../util.ts";

const input = getInput();
const height = input.length;
const width = input[0].length;

function solve(r) {
    let grid = new Uint32Array(width * height);
    grid.fill(1 << 30);

    let start = null;
    let end = null;

    for (let y = 1; y < height - 1; y++) {
        for (let x = 1; x < width - 1; x++) {
            if (input[y][x] == 'S') {
                start = [x, y];
            }
            if (input[y][x] == 'E') {
                end = [x, y];
            }
        }
    }

    let x = end[0];
    let y = end[1];
    let dx = 0; // todo
    let dy = 1;
    let i = 0;
    grid[x + y * width] = i;

    let path = [[x, y]];

    while (true) {
        while (true) {
            x += dx;
            y += dy;
            if (input[y][x] == "#") break;

            path.push([x, y]);
            i++
            grid[x + y * width] = i;
        }
        x -= dx;
        y -= dy;

        if (x == start[0] && y == start[1]) break;

        if (input[y - dx][x + dy] != "#") {
            [dx, dy] = [dy, -dx];
        }
        if (input[y + dx][x - dy] != "#") {
            [dx, dy] = [-dy, dx];
        }
    }

    // let count = 0;
    // for (let i = 0; i < path.length - 100;) {
    //     const [x1, y1] = path[i];

    //     let iskip = Infinity

    //     for (let j = i + 100; j < path.length;) {
    //         const [x2, y2] = path[j];

    //         let cheatLength = Math.abs(x1 - x2) + Math.abs(y1 - y2);

    //         if (cheatLength > r) {
    //             let jskip = cheatLength - r
    //             iskip = Math.min(iskip, jskip >> 1)
    //             j += jskip
    //         } else {
    //             count += (j - i) - cheatLength >= 100
    //             j++
    //         }
    //     }

    //     i += Math.max(1, iskip);
    // }
    // return count;

    const max = grid[start[0] + start[1] * width];
    let count = 0;

    for (let y = 1; y < height - 1; y++) {
        for (let x = 1; x < width - 1; x++) {
            const sv = grid[x + y * width];
            if (sv > max) continue;

            for (let y1 = -r; y1 <= r; y1++) {
                const y2 = y + y1;
                if (y2 < 0 || y2 >= height) continue;

                const r2 = r - Math.abs(y1);

                for (let x1 = -r2; x1 <= r2; x1++) {
                    const x2 = x + x1;
                    if (x2 < 0 || x2 >= width) continue;

                    const ev = grid[x2 + y2 * width];
                    const l = Math.abs(x1) + Math.abs(y1);
                    if (ev + 100 + l - 1 < sv) {
                        count++;
                    }
                }
            }

        }
    }

    return count;
}

export function part1() {
    return solve(2);
}

export function part2() {
    return solve(20);
}

import { checkAnswers } from "../test.ts";
checkAnswers();
