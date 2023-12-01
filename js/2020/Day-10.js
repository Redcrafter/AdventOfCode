import { getInput } from "../util.js";

const input = new Int32Array(getInput().map(x => parseInt(x)));

export function part1() {
    let s = input.slice();
    s.sort();

    let one = 0;
    let three = 1;

    let prev = 0;
    for (let i = 0; i < s.length; i++) {
        let diff = s[i] - prev;
        if (diff == 1) {
            one++;
        } else if (diff == 3) {
            three++;
        }
        prev = s[i];
    }

    return one * three;
}

export function part2() {
    let inp = input.slice();
    inp.sort();

    let vals = new Array(inp.length).fill(0);

    if (inp[0] <= 3) vals[0]++;
    if (inp[1] <= 3) vals[1]++;
    if (inp[2] <= 3) vals[2]++;

    for (let i = 0; i < inp.length; i++) {
        const v = inp[i];
        const n = vals[i];

        if (v + 3 >= inp[i + 1]) vals[i + 1] += n;
        if (v + 3 >= inp[i + 2]) vals[i + 2] += n;
        if (v + 3 >= inp[i + 3]) vals[i + 3] += n;
    }

    return vals[vals.length - 1];
}


import { checkAnsweres } from "../test.js";
checkAnsweres();
