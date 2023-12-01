import { arraySplit, extractNumbers, getInput, sum } from "../util.js";

const input = arraySplit(getInput(), 6).map(x => {
    let i = extractNumbers(x[0])[0];
    let nums = extractNumbers(x[1]);
    let func = new Function("old", `return ${x[2].substr(19)}`);
    let mod = extractNumbers(x[3])[0];
    let t = extractNumbers(x[4])[0];
    let f = extractNumbers(x[5])[0];

    let add = func(0);
    let mul = 1;
    let pow = 0;
    if (add == 0) {
        mul = func(1);
        if (mul == 1) {
            mul = 0;
            pow = 1;
        }
    }

    return { i, nums, func, mod, t, f, add, mul, pow };
});

export function part1() {
    const b = new Int32Array(input.length);

    const stacks = new Array(input.length);
    for (let k = 0; k < input.length; k++) {
        stacks[k] = input[k].nums.slice();
    }

    for (let j = 0; j < 20; j++) {
        for (let i = 0; i < input.length; i++) {
            const item = input[i];

            const s = stacks[i]
            b[i] += s.length;

            while (s.length != 0) {
                const n = s.pop();
                const m = item.pow ? ((n * n) / 3) | 0 : (((n * item.mul + item.add) | 0) / 3) | 0;

                let next;
                if (m % item.mod == 0) {
                    next = item.t;
                } else {
                    next = item.f;
                }

                stacks[next].push(m);
            }
        }
    }

    b.sort();
    return b.at(-1) * b.at(-2);
}

export function part2() {
    const b = new Int32Array(input.length);
    const t = input.reduce((a, b) => a * b.mod, 1);

    const stacks = new Array(input.length);
    for (let k = 0; k < input.length; k++) {
        stacks[k] = input[k].nums.slice();
    }

    for (let i = 0; i < 10000; i++) {
        for (let j = 0; j < input.length; j++) {
            const item = input[j];

            const s = stacks[j]
            b[j] += s.length;

            while (s.length != 0) {
                const n = s.pop();
                const m = item.pow ? ((n * n) % t) | 0 : (((n * item.mul + item.add) | 0) % t) | 0;

                let next;
                if (m % item.mod == 0) {
                    next = item.t;
                } else {
                    next = item.f;
                }
                stacks[next].push(m);
            }
        }
    }

    b.sort();
    return b.at(-1) * b.at(-2);
}

import { checkAnswers } from "../test.js";
checkAnswers();
