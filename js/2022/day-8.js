import { getInput } from "../util.js";
const input = getInput().flatMap(x => [...x].map(x => +x));

const size = 99;

function calcSet() {
    let vis = new Set();

    function ray(x, y, dx, dy) {
        let height = -1;

        while (height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            let v = input[x + y * size];
            if (v > height) {
                height = v;
                vis.add(x + y * size);
            }

            x += dx;
            y += dy;
        }
    }

    for (let i = 0; i < size; i++) {
        ray(0, i, 1, 0);
        ray(98, i, -1, 0);

        ray(i, 0, 0, 1);
        ray(i, 98, 0, -1);
    }

    return vis;
}

export function part1() {
    return calcSet().size;
}

export function part2() {
    function score(x, y, dx, dy) {
        let height = input[x + y * size];

        let score = 0;

        x += dx;
        y += dy;

        while (x < size && y < size & x >= 0 && y >= 0) {
            let v = input[x + y * size];
            score++;
            if (v >= height) {
                break;
            }
            x += dx;
            y += dy;
        }

        return score;
    }

    let best = 0;
    let vis = calcSet();
    for (const item of vis) {
        let x = item % size;
        let y = (item / size) | 0;

        let s = score(x, y, 1, 0) * score(x, y, -1, 0) * score(x, y, 0, 1) * score(x, y, 0, -1);
        if (s > best) best = s;
    }

    return best;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.log(part1() == 1859);
    console.log(part2() == 332640);
}
