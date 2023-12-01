import { getInput } from "../util.js";

const input = getInput();

const inputStr = input[0];
const inputRules = input.slice(1).map(x => x.split(/ -> /));

const letters = new Map([..."PKCBFNSHVO"].map((x, i) => [x.charCodeAt(0), i]));

export function part1_old() {
    let str = Array.from(inputStr);
    let map = new Map(inputRules);

    for (let i = 0; i < 10; i++) {
        let next = [];

        for (let j = 0; j < str.length - 1; j++) {
            let sub = str[j] + str[j + 1];
            let ins = map.get(sub);

            next.push(str[j]);
            if (ins) {
                next.push(ins);
            }
        }
        next.push(str[str.length - 1]);

        str = next;
    }

    let counts = new Map();
    for (const item of str) {
        counts.set(item, (counts.get(item) ?? 0) + 1);
    }

    return Math.max(...counts.values()) - Math.min(...counts.values());
}

function run(iters) {
    let matrix1 = new Array(100).fill(0);
    let matrix2 = new Array(100).fill(0);
    let counts = new Array(10).fill(0);

    counts[letters.get(inputStr.charCodeAt(0))]++;
    for (let j = 1; j < inputStr.length; j++) {
        let a = letters.get(inputStr.charCodeAt(j - 1));
        let b = letters.get(inputStr.charCodeAt(j));
        matrix1[a + b * 10]++;
        counts[b]++;
    }

    let rules = [];
    for (const [inp, out] of inputRules) {
        let a = letters.get(inp.charCodeAt(0));
        let b = letters.get(inp.charCodeAt(1));
        let c = letters.get(out.charCodeAt(0));

        rules[a + b * 10] = [a + c * 10, c + b * 10, c];
    }

    for (let i = 0; i < iters; i++) {
        for (let j = 0; j < rules.length; j++) {
            const item = rules[j];
            const val = matrix1[j];
            matrix1[j] = 0;

            matrix2[item[0]] += val;
            matrix2[item[1]] += val;
            counts[item[2]] += val;
        }
        let temp = matrix1;
        matrix1 = matrix2;
        matrix2 = temp;
    }

    /*let str = "";
    for (let i = 0; i < 100; i++) {
        str += matrix[i].toString().padStart(12, " ") + ", ";
        if(i % 10 == 9) {
            str += "\n";
        }
    }
    console.log(str);*/

    return Math.max(...counts) - Math.min(...counts);
}

export function part1() {
    return run(10);
}

export function part2() {
    return run(40);
}

import { checkAnswers } from "../test.js";
checkAnswers();
