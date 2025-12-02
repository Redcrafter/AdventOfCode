import { getInput, arraySplit, parseInt } from "../util.js";

const input = getInput();

export function part1() {
    let res = 0;

    for (const item of input[0].split(",")) {
        const [a, b] = item.split("-").map(x => parseInt(x));

        for (let i = a; i <= b; i++) {
            const str = i.toString();
            if (str.length % 2 == 0 && str.slice(0, str.length / 2) == str.slice(str.length / 2)) {
                res += i;
            }
        }
    }

    return res;
}

export function part2() {
    let res = 0;

    for (const item of input[0].split(",")) {
        const [a, b] = item.split("-").map(x => parseInt(x));
        for (let i = a; i <= b; i++) {
            const str = i.toString();
            for (let j = 1; j <= str.length / 2; j++) {
                if (str.length % j != 0) continue;
                const sub = arraySplit(str, j);
                if (sub.every(x => x == sub[0])) {
                    res += i;
                    break;
                }
            }
        }
    }
    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
