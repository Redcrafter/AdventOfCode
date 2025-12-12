import { getInput } from "../util.ts";

const input = getInput().map(x => x.split(" "));

function check(inp) {
    return inp[0] + 5 == inp[13] &&
        inp[1] == inp[12] &&
        inp[2] - 8 == inp[3] &&
        inp[4] + 2 == inp[5] &&
        inp[6] + 7 == inp[11] &&
        inp[7] - 5 == inp[10] &&
        inp[8] - 6 == inp[9];
}

function print() {
    let str = "";
    for (const ins of input) {
        switch (ins[0]) {
            case "inp": str += `${ins[1]} = read()`; break;
            case "add": str += `${ins[1]} = ${ins[1]} + ${ins[2]}`; break;
            case "mul": str += `${ins[1]} = ${ins[1]} * ${ins[2]}`; break;
            case "div": str += `${ins[1]} = ${ins[1]} / ${ins[2]}`; break;
            case "mod": str += `${ins[1]} = ${ins[1]} % ${ins[2]}`; break;
            case "eql": str += `${ins[1]} = ${ins[1]} == ${ins[2]}`; break;
        }
        str += "\n";
    }
    console.log(str);
}

export function part1() {
    return 49917929934999;
}

export function part2() {
    return 11911316711816;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
