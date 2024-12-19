import { getInput } from "../util.js";

const input = getInput();
const input1 = input[0].split(", ");
const input2 = input.slice(1);

export function part1() {
    const reg = new RegExp(`^(${input1.join("|")})+$`);
    return input2.reduce((v, x) => v + reg.test(x), 0);
}

export function part2() {
    const known = new Map();

    function testDesign(str) {
        if (str.length == 0) return 1;
        if (known.has(str))
            return known.get(str);

        let res = 0;
        for (const el of input1) {
            if (str.startsWith(el)) {
                res += testDesign(str.substring(el.length));
            }
        }

        known.set(str, res);
        return res;
    }

    let res = 0;
    for (const line of input2) {
        res += testDesign(line, 0);
    }
    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
