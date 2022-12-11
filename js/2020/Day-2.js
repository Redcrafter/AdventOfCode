import { getInput } from "../util.js";
const input = getInput().map(x => x.split(/(\d+)-(\d+) (\w): /).slice(1));

function counteLetter(str, l) {
    const asdf = l.charAt(0);

    let c = 0;
    for (let i = 0; i < str.length; i++) {
        c += str.charAt(i) == asdf;
    }
    return c;
}

export function part1() {
    let part1 = 0;

    for (const item of input) {
        const c = counteLetter(item[3], item[2]);
        part1 += (c >= item[0] && c <= item[1]);
    }

    return part1;
}

export function part2() {
    let part2 = 0;

    for (const item of input) {
        part2 += (item[3].charAt(item[0] - 1) == item[2]) ^ (item[3].charAt(item[1] - 1) == item[2]);
    }

    return part2;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
