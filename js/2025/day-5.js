import { extractNumbers, getInput, parseInt } from "../util.js";

const input = getInput();

const in1 = input.slice(0, 182).map(x => x.split("-").map(x => parseInt(x)));
const inp2 = input.slice(182).map(x => parseInt(x));

export function part1() {
    let res = 0;

    function check(val) {
        for (let i = 0; i < in1.length; i++) {
            const [start, end] = in1[i];
            if (val >= start && val <= end) return true;
        }
        return false;
    }

    for (let i = 0; i < inp2.length; i++) {
        const line = inp2[i];
        res += check(line);
    }

    return res;
}

export function part2() {
    let res = 0;

    const asd = in1.slice();
    asd.sort((a, b) => a[0] - b[0]);

    let end = 0;

    for (let i = 0; i < asd.length; i++) {
        let [a, b] = asd[i];

        if (a <= end) {
            a = end + 1;
        }
        end = Math.max(end, b);

        if (a <= b) {
            res += b - a + 1;
        }
    }
    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
