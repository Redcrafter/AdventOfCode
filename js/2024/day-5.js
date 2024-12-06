import { extractNumbers, getInput } from "../util.js";

const [_input1, _input2] = getInput(false).join("\n").trim().split("\n\n");
const input1 = extractNumbers(_input1.split("\n"));
const input2 = extractNumbers(_input2.split("\n")).map(x => new Uint8Array(x));

function check(map, page) {
    for (let i = page.length - 1; i >= 0; i--) {
        const a = page[i];
        for (let j = i - 1; j >= 0; j--) {
            if (map[a + page[j] * 100] === 1) {
                return false;
            }
        }
    }
    return true;
}

export function part1() {
    const map = new Uint8Array(100 * 100);
    for (const el of input1) map[el[0] + el[1] * 100] = 1;

    let result = 0;
    for (const item of input2) {
        if (check(map, item)) result += item[(item.length / 2) | 0];
    }
    return result;
}

export function part2() {
    let result = 0;

    const map = new Uint8Array(100 * 100);
    for (const el of input1) map[el[0] + el[1] * 100] = 1;

    for (const item of input2) {
        let eq = true;
        const sorted = item.slice();
        // insertion sort + equality check
        for (let i = 1; i < sorted.length; i++) {
            const a = sorted[i];
            let j = i;
            for (; j > 0 && map[a + sorted[j - 1] * 100] == 1; j--) {
                sorted[j] = sorted[j - 1];
                eq = false;
            }
            sorted[j] = a;
        }
        if (!eq) result += sorted[(sorted.length / 2) | 0];
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
