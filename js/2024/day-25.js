import { arraySplit, getInput } from "../util.ts";

const input = arraySplit(getInput(false), x => x.length == 0);
input.pop();

export function part1() {
    const locks = [];
    const keys = [];

    for (let i = 0; i < input.length; i++) {
        const el = input[i];

        let counts = [];
        for (let x = 0; x < 5; x++) {
            let c = -1;
            for (let y = 0; y < 7; y++) {
                if (el[y][x] == "#") c++;
            }
            counts.push(c);
        }

        if (el[0] == "#####") {
            locks.push(counts);
        } else {
            keys.push(counts);
        }
    }

    let result = 0;

    for (const l of locks) {
        for (const k of keys) {
            let ok = true;

            for (let i = 0; i < 5; i++) {
                if (l[i] + k[i] > 5) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                result++;
            }
        }
    }

    return result;
}

export function part2() {
    return 0;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
