import { getInput } from "../util.js";
const input = getInput()[0].split(",").map(x => parseInt(x));

function part1_old() {
    let sub = input.slice();

    for (let i = 0; i < 80; i++) {
        let len = sub.length;
        for (let j = 0; j < len; j++) {
            if (sub[j] == 0) {
                sub[j] = 6
                sub.push(8);
            } else {
                sub[j]--;
            }
        }
    }

    return sub.length;
}

function runStuff(days) {
    let buckets = new Array(9).fill(0);

    for (let i = 0; i < input.length; i++) {
        buckets[input[i]]++;
    }

    for (let i = 0; i < days; i++) {
        let temp = buckets[0];

        buckets[0] = buckets[1];
        buckets[1] = buckets[2];
        buckets[2] = buckets[3];
        buckets[3] = buckets[4];
        buckets[4] = buckets[5];
        buckets[5] = buckets[6];
        buckets[6] = buckets[7] + temp;
        buckets[7] = buckets[8];
        buckets[8] = temp;
    }

    let sum = 0;
    for (let i = 0; i < buckets.length; i++) {
        sum += buckets[i];
    }
    return sum;
}

export function part1() {
    return runStuff(80);
}

export function part2() {
    return runStuff(256);
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 383160);
    console.assert(part2() == 1721148811504);
}
