import { getInput } from "../util.js";

const input = getInput();

const height = input.length;
const width = input[0].length;

export function part1() {
    let result = 0;

    let seen = new Set();
    function step(x, y) {
        let t = input[y][x];
        if (t == '#' || seen.has(x + y * width)) return;

        if (x == width - 2 && y == height - 1) {
            result = Math.max(result, seen.size);
            return;
        }

        seen.add(x + y * width);
        if (t == ".") {
            step(x - 1, y);
            step(x + 1, y);
            if (y > 0) step(x, y - 1);
            step(x, y + 1);
        }
        if (t == '^') {
            step(x, y - 1);
        }
        if (t == 'v') {
            step(x, y + 1);
        }
        if (t == '>') {
            step(x + 1, y);
        }
        if (t == '<') {
            step(x - 1, y);
        }

        seen.delete(x + y * width);
    }

    step(1, 0);
    return result
}

export function part2() {
    let result = 0;

    let seen = new Set();
    function step(x, y) {
        let t = input[y][x];
        if (t == '#' || seen.has(x + y * width)) return;

        if (x == width - 2 && y == height - 1) {
            if (seen.size > result) {
                result = seen.size;
                console.log(result);
            }
            result = Math.max(result, seen.size);
            return;
        }

        seen.add(x + y * width);
        step(x - 1, y);
        step(x + 1, y);
        if (y > 0) step(x, y - 1);
        step(x, y + 1);

        seen.delete(x + y * width);
    }

    step(1, 0);
    return result
}

import { checkAnswers } from "../test.js";
checkAnswers();
