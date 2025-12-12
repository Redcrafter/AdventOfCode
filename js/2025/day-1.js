import { getInput, parseInt } from "../util.ts";

const input = getInput();

export function part1() {
    let res = 0;

    let num = 50;
    for (let i = 0; i < input.length; i++) {
        const item = input[i];
        const v = parseInt(item, 1);

        if (item[0] == "R") {
            num = (num + v) % 100;
        } else {
            num = (num - v + 1000) % 100;
        }
        if (num == 0) {
            res++;
        }
    }
    return res;
}

export function part2() {
    let res = 0;

    let dial = 50;
    for (let i = 0; i < input.length; i++) {
        const item = input[i];
        const v = parseInt(item, 1);

        if (item[0] == "R") {
            res += Math.floor((dial + v) / 100);
            dial = (dial + v) % 100;
        } else {
            if (dial == 0)
                res--;
            dial = dial - v + 1000;
            res += 10 - Math.floor(dial / 100);
            dial = dial % 100;
            if (dial == 0)
                res++;
        }
    }
    return res;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
