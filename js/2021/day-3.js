
import { getInput } from "../util.js";
const input = getInput().map(x => parseInt(x, 2));

function findCommon(arr, mask) {
    let sum = 0;
    for (let i = 0; i < arr.length; i++) {
        sum += arr[i] & mask;
    }
    return sum / mask;
}

export function part1() {
    let gamma = 0;

    for (let i = 0; i < 12; i++) {
        let mask = 1 << i;
        if (findCommon(input, mask) > input.length / 2) gamma |= mask;
    }

    return gamma * (gamma ^ 0b111111111111);
}

export function part2() {
    let mask = 1 << 11;
    let root = (findCommon(input, mask) >= input.length / 2) * mask;
    let a = [];
    let b = [];

    for (const x of input) {
        if((x & mask) == root) a.push(x)
        else b.push(x);
    }

    for (let i = 10; i >= 0 && a.length > 1; i--) {
        let mask = (1 << i);
        let common = findCommon(a, mask) >= a.length / 2;
        a = a.filter(x => (x & mask) == (common * mask));
    }
    for (let i = 10; i >= 0 && b.length > 1; i--) {
        let mask = (1 << i);
        let common = findCommon(b, mask) >= b.length / 2;
        b = b.filter(x => (x & mask) != (common * mask));
    }

    return a[0] * b[0];
}

import { checkAnsweres } from "../test.js";
checkAnsweres();