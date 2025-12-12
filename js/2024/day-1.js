import { getInput, parseInt, radixSortUint32 } from "../util.ts";

const input = getInput();

export function part1() {
    let result = 0;

    const l = new Uint32Array(input.length);
    const r = new Uint32Array(input.length);

    for (let i = 0; i < input.length; i++) {
        const line = input[i];
        l[i] = parseInt(line);
        r[i] = parseInt(line, 8);
    }

    radixSortUint32(l);
    radixSortUint32(r);

    for (let i = 0; i < l.length; i++) {
        result += Math.abs(l[i] - r[i]);
    }

    return result;
}

export function part2() {
    let result = 0;

    const r = new Map();

    for (let i = 0; i < input.length; i++) {
        const b = parseInt(input[i], 8);
        r.set(b, (r.get(b) ?? 0) + 1);
    }

    for (let i = 0; i < input.length; i++) {
        const a = parseInt(input[i]);
        result += a * (r.get(a) ?? 0);
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
