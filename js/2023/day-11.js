import { getInput } from "../util.js";

const input = getInput().map(x => [...x]);

function solve(add) {
    let galac = [];
    for (let y = 0; y < input.length; y++) {
        const line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line[x] == "#") {
                galac.push([x, y]);
            }
        }
    }

    for (let y = input.length - 1; y >= 0; y--) {
        if (!input[y].includes("#")) {
            for (const g of galac) {
                if (g[1] > y) {
                    g[1] += add;
                }
            }
        }
    }

    const width = input[0].length;
    for (let x = width - 1; x >= 0; x--) {
        let ok = true;
        for (let y = 0; y < input.length; y++) {
            if (input[y][x] == '#') {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (const g of galac) {
                if (g[0] > x) {
                    g[0] += add;
                }
            }
        }
    }

    let res = 0;
    for (let i = 0; i < galac.length; i++) {
        const [x1, y1] = galac[i];

        for (let j = i + 1; j < galac.length; j++) {
            const [x2, y2] = galac[j];
            res += Math.abs(x1 - x2) + Math.abs(y1 - y2)
        }
    }

    return res;
}

export function part1() {
    return solve(1);
}

export function part2() {
    return solve(1000000 - 1);
}

import { checkAnswers } from "../test.js";
checkAnswers();
