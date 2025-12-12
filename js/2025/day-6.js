import { extractNumbers, getInput, parseInt, zip } from "../util.ts";

const input = getInput();

export function part1() {
    const nums = extractNumbers(input.slice(0, 4));
    const ops = input[4].replaceAll("  ", " ").replaceAll("  ", " ").replaceAll("  ", " ").split(" ");

    let res = 0;
    for (let i = 0; i < nums[0].length; i++) {
        if (ops[i] == "+") {
            for (let j = 0; j < nums.length; j++) {
                res += nums[j][i];
            }
        } else {
            let v = 1;
            for (let j = 0; j < nums.length; j++) {
                v *= nums[j][i];
            }
            res += v;
        }
    }

    return res;
}

export function part2() {
    let res = 0;

    const shit = zip(...input);

    for (let i = 0; i < input[0].length;) {
        const op = input[4][i];
        if (op == "_") break;

        let next = i + 1;
        while (input[4][next] == " ") {
            next++;
        }
        const len = next - i - 1;

        if (op == "+") {
            for (let j = 0; j < len; j++) {
                res += parseInt(shit[i + j].slice(0, 4).join("").trim());
            }
        } else {
            let v = 1;
            for (let j = 0; j < len; j++) {
                v *= parseInt(shit[i + j].slice(0, 4).join("").trim());
            }
            res += v;
        }
        i = next;
    }


    return res;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
