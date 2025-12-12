import { extractNumbers, getInput } from "../util.ts";

const input = extractNumbers(getInput()).map(x => new Float64Array(x));

function test1(vals, res, i) {
    const a = vals[i];

    if (i == 2) {
        const b = vals[i - 1];
        return (a + b == res) || (a * b == res);
    } else {
        return ((res % a) == 0 && test1(vals, res / a, i - 1)) || (res >= a && test1(vals, res - a, i - 1));
    }
}

export function part1() {
    let result = 0;
    // for (const item of input) {
    for (let i = 0; i < input.length; i++) {
        const item = input[i];

        if (test1(item, item[0], item.length - 1)) console.log(i);
        result += item[0] * test1(item, item[0], item.length - 1);
    }
    return result;
}

// way faster then doing 10**log10(x)
function digits(x) {
    let r = 10;
    while (x >= 10) {
        x /= 10;
        r *= 10;
    }
    return r;
}

function test2(vals, res, i) {
    const a = vals[i];

    if (i == 2) {
        const b = vals[i - 1];
        return (a + b) == res || (a * b == res) || ((b * digits(a) + a) == res);
    } else {
        if ((res % a) == 0 && test2(vals, res / a, i - 1)) return true; // reduces a lot and is fast

        const l = digits(a);
        if (a == (res % l) && test2(vals, Math.floor(res / l), i - 1)) return true; // reduces a lot and is slow

        return res >= a && test2(vals, res - a, i - 1); // reduces a little
    }
}

export function part2() {
    let result = 0;
    for (const item of input) {
        result += item[0] * test2(item, item[0], item.length - 1);
    }
    return result;

}

import { checkAnswers } from "../test.ts";
checkAnswers();
