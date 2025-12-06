import { getInput, parseInt } from "../util.js";

const input = getInput();

export function part1() {
    let res = 0;

    for (let i = 0; i < input.length; i++) {
        const line = [...input[i]].map(x => x.charCodeAt(0) - 48);

        const max = Math.max(...line.slice(0, -1));
        const ind = line.indexOf(max);
        const next = Math.max(...line.slice(ind + 1));

        res += max * 10 + next;
    }

    return res;
}

export function part2() {
    let res = 0;

    for (let i = 0; i < input.length; i++) {
        let line = [...input[i]].map(x => parseInt(x));

        let val = 0;
        for (let j = 11; j >= 1; j--) {
            const max = Math.max(...line.slice(0, -j));
            const ind = line.indexOf(max);
            line = line.slice(ind + 1);

            val = val * 10 + max;
        }

        const max = Math.max(...line);
        val = val * 10 + max;
        res += val;
    }

    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
