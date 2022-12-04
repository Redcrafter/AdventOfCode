import { getInput } from "../util.js";

const forward = [1, 0];
const down = [0, 1];
const up = [0, -1];

const dirs = { forward, down, up };

const input = getInput().map(x => {
    let [a, b] = x.split(" ");
    return [dirs[a], parseInt(b)];
});

export function part1() {
    let depth = 0;
    let dist = 0;

    for (const [a, b] of input) {
        dist += b * a[0];
        depth += b * a[1];
    }

    return depth * dist;
}

export function part2() {
    let depth = 0;
    let dist = 0;
    let aim = 0;

    for (const [a, x] of input) {
        if (a === forward) {
            dist += x;
            depth += aim * x;
        } else if (a === down) {
            aim += x;
        } else if (a === up) {
            aim -= x;
        }
    }

    return depth * dist;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 1507611);
    console.assert(part2() == 1880593125);
}