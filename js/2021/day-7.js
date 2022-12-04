import { getInput } from "../util.js";
const input = getInput()[0].split(",").map(x => parseInt(x));

export function part1() {
    let min = Infinity;
    let max = 0;

    for (const item of input) {
        min = Math.min(min, item);
        max = Math.max(max, item);
    }

    function test(i) {
        let cost = 0;
        for (let j = 0; j < input.length; j++) {
            cost += Math.abs(input[j] - i);
        }
        return cost;
    }

    let best = Infinity;

    let l = 0;
    let r = input.length - 1;
    while (l + 1 < r) {
        let mid = Math.floor((l + r) / 2);

        let a = test(mid);
        let b = test(mid + 1);

        if (a < best) best = a;
        if (b < best) best = b;

        if (a < b) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return best;
}

export function part2() {
    let min = Infinity;
    let max = 0;

    for (const item of input) {
        min = Math.min(min, item);
        max = Math.max(max, item);
    }

    function test(i) {
        let cost = 0;
        for (let j = 0; j < input.length; j++) {
            let val = Math.abs(input[j] - i);
            cost += val * (val + 1) / 2;
        }
        return cost;
    }

    let best = Infinity;

    let l = 0;
    let r = input.length - 1;
    while (l + 1 < r) {
        let mid = Math.floor((l + r) / 2);

        let a = test(mid);
        let b = test(mid + 1);

        if (a < best) best = a;
        if (b < best) best = b;

        if (a < b) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return best;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 336131);
    console.assert(part2() == 92676646);
}
