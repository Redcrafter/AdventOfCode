import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    let result = 0;

    for (const line of input) {
        let nums = line.split(" ").map(x => parseInt(x));

        let layers = [nums];

        while (true) {
            let last = layers[layers.length - 1];
            if (last.every(x => x == last[0]))
                break;

            let n = new Array(last.length - 1);
            for (let i = 0; i < last.length - 1; i++) {
                n[i] = last[i + 1] - last[i];
            }
            layers.push(n);
        }

        let v = layers[layers.length - 1][0];
        for (let i = layers.length - 2; i >= 0; i--) {
            let l = layers[i];
            v = l[l.length - 1] + v;
        }

        result += v;
    }

    return result;
}

export function part2() {
    let result = 0;

    for (const line of input) {
        let nums = line.split(" ").map(x => parseInt(x));

        let layers = [nums];

        while (true) {
            let last = layers[layers.length - 1];
            if (last.every(x => x == last[0]))
                break;

            let n = new Array(last.length - 1);
            for (let i = 0; i < last.length - 1; i++) {
                n[i] = last[i + 1] - last[i];
            }
            layers.push(n);
        }

        let v = layers[layers.length - 1][0];
        for (let i = layers.length - 2; i >= 0; i--) {
            v = layers[i][0] - v;
        }

        result += v;
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
