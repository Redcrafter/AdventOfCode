import { getInput } from "../util.ts";

const input = getInput().map(x => x.split(" -> ").map(y => y.split(",").map(x => parseInt(x))));

const width = 1000;
const height = 200;

function print(grid, h, w0, w1) {
    for (let y = 0; y < h; y++) {
        let str = "";
        for (let x = w0; x <= w1; x++) {
            let val = grid[x + y * width];
            if (x == 500 && y == 0) {
                str += "+";
            } else if (val == -1) {
                str += "█";
            } else if (val == 1) {
                str += "░";
            } else {
                str += " ";
            }

        }
        console.log(str);
    }
}

function calcGrid() {
    const grid = new Int32Array(width * height);
    let maxY = 0;

    function set(x, y) {
        grid[x + y * width] = -1;
    }

    for (let i = 0; i < input.length; i++) {
        const item = input[i];

        let p = item[0];

        for (let i = 1; i < item.length; i++) {
            const c = item[i];

            if (c[0] == p[0]) {
                const s = Math.sign(c[1] - p[1]);

                for (let y = p[1]; y != c[1]; y += s) {
                    set(c[0], y);
                }
                maxY = Math.max(maxY, c[1]);
            } else {
                const s = Math.sign(c[0] - p[0]);

                for (let x = p[0]; x != c[0]; x += s) {
                    set(x, c[1]);
                }
            }

            p = c;
            set(c[0], c[1]);
        }
    }

    return [grid, maxY + 1];
}

export function part1() {
    const [grid, maxY] = calcGrid();

    let c = 0;
    function rec(x, y) {
        if (grid[x + y * width] != 0)
            return false;

        if (y == maxY)
            return true;

        const v = rec(x, y + 1) || rec(x - 1, y + 1) || rec(x + 1, y + 1);
        if (!v) {
            grid[x + y * width] = 1;
            c++;
        }
        return v;
    }

    rec(500, 0);
    // print(grid, maxY, 400, 600);
    return c;
}

export function part2() {
    const [grid, maxY] = calcGrid();

    let c = 0;
    function rec(x, y) {
        if (grid[x + y * width] != 0) return;
        grid[x + y * width] = 1;

        c++;
        if (y == maxY) return;

        rec(x, y + 1);
        rec(x - 1, y + 1);
        rec(x + 1, y + 1);
    }

    rec(500, 0);
    // print(grid, maxY, 400, 600);
    return c;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
