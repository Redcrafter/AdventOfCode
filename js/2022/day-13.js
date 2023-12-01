import { arraySplit, getInput } from "../util.js";

const input1 = arraySplit(getInput(false), x => x == "").map(x => x.map(y => JSON.parse(y))).filter(x => x.length);
const input2 = getInput().map(x => JSON.parse(x));

function compare(a, b) {
    if (typeof a == "number" && typeof b == "number") {
        return b - a;
    }
    if (Array.isArray(a) && Array.isArray(b)) {
        for (let i = 0; true; i++) {
            if (i >= a.length && i >= b.length) return 0;
            if (i >= a.length) return 1;
            if (i >= b.length) return -1;

            let r = compare(a[i], b[i]);
            if (r != 0) return r;
        }
    }

    if (typeof a == "number") {
        return compare([a], b);
    } else {
        return compare(a, [b]);
    }
}

export function part1() {
    let res = 0;

    for (let i = 0; i < input1.length; i++) {
        const [a, b] = input1[i];
        if (compare(a, b) >= 1) res += i + 1;
    }

    return res;
}

export function part2() {
    let d1 = [[2]];
    let d2 = [[6]];
    let i1 = 1;
    let i2 = 2;

    for (let i = 0; i < input2.length; i++) {
        if (compare(input2[i], d1) >= 1) i1++;
        if (compare(input2[i], d2) >= 1) i2++;
    }

    return i1 * i2;
}

import { checkAnswers } from "../test.js";
checkAnswers();
