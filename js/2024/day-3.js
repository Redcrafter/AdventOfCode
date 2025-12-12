import { getInput } from "../util.ts";

const input = getInput();

// assuming the string only contains valid chars
export function parseInt(str) {
    let val = 0;
    for (let i = 0; i < str.length; i++) {
        val = val * 10 + str.charCodeAt(i) - 48;
    }
    return val;
}

export function part1() {
    let result = 0;
    for (let i = 0; i < input.length; i++) {
        for (const item of input[i].matchAll(/mul\((\d+),(\d+)\)/g)) {
            result += parseInt(item[1]) * parseInt(item[2]);
        }
    }
    return result;
}

export function part2() {
    let result = 0;
    let en = true;

    for (let i = 0; i < input.length; i++) {
        for (const item of input[i].matchAll(/mul\((\d+),(\d+)\)|do\(\)|don't\(\)/g)) {
            if (item[0] === "do()") {
                en = true;
            } else if (item[0] === "don't()") {
                en = false;
            } else if (en) {
                result += parseInt(item[1]) * parseInt(item[2]);
            }
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
