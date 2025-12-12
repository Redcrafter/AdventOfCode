import { getInput } from "../util.ts";

const input = getInput();

function parse(str) {
    let v = 0;
    for (let i = 0; i < str.length; i++) {
        v *= 5;
        switch (str[i]) {
            case "=": v -= 2; break;
            case "-": v -= 1; break;
            case "1": v += 1; break;
            case "2": v += 2; break;
        }
    }
    return v;
}

function toString(val) {
    let res = [];
    let i = 0;

    while (val != 0) {
        let m = val % 5;
        if (m == 0) {
            if (res[i]) {
                // res[i] = "1";
            } else res.push("0");
        } else if (m == 1) {
            if (res[i]) {
                res[i] = "2";
            } else res.push("1");
        } else if (m == 2) {
            if (res[i]) {
                res[i] = "="
                res.push("1");
            } else res.push("2");
        } else if (m == 3) {
            if (res[i]) {
                res[i] = "-";
                res.push("1");
            } else res.push("=", "1");
        } else if (m == 4) {
            if (res[i]) {
                res[i] = "0";
                res.push("1");
            } else res.push("-", "1");
        }

        i++;
        val = Math.floor(val / 5);
    }

    return res.reverse().join("");
}

export function part1() {
    let sum = 0;
    for (const item of input) {
        sum += parse(item);
    }
    return toString(sum);
}

export function part2() {
    return 0;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
