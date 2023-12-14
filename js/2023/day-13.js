import { getInput } from "../util.js";

const input = getInput(false).join("\n").split("\n\n").map(x => x.split("\n"));

// split before ind
function vert(pattern, ind) {
    let bad = 0;

    let w = pattern[0].length;
    let s = Math.min(ind, pattern.length - ind);
    if (s <= 0)
        return false;

    for (let i = 0; i < s; i++) {
        for (let j = 0; j < w; j++) {
            if (pattern[ind - i - 1][j] != pattern[ind + i][j]) {
                bad++;
            }
        }
    }
    return bad;
}

function rotate(pattern) {
    let res = [];
    for (let i = 0; i < pattern[0].length; i++) {
        let l = [];
        for (let j = 0; j < pattern.length; j++) {
            l.push(pattern[j][i])
        }
        res.push(l.join(""));
    }
    return res;
}

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const pattern = input[i];

        for (let j = 1; j < pattern.length; j++) {
            if (vert(pattern, j) == 0) {
                result += j * 100;
            }
        }

        let r = rotate(pattern);
        for (let j = 1; j < r.length; j++) {
            if (vert(r, j) == 0) {
                result += j;
            }
        }
    }

    return result;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const pattern = input[i];

        for (let j = 1; j < pattern.length; j++) {
            if (vert(pattern, j) == 1) {
                result += j * 100;
            }
        }

        let r = rotate(pattern);
        for (let j = 1; j < r.length; j++) {
            if (vert(r, j) == 1) {
                result += j;
            }
        }
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
