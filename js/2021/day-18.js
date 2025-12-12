import { getInput } from "../util.ts";

const input = getInput().map(x => JSON.parse(x));

function addToRight(pair, val) {
    if (typeof pair[1] === "number") {
        pair[1] += val;
    } else {
        addToRight(pair[1], val);
    }
}
function addToLeft(pair, val) {
    if (typeof pair[0] === "number") {
        pair[0] += val;
    } else {
        addToLeft(pair[0], val);
    }
}

function explode(leftFunc, rightFunc, pair, depth) {
    if (typeof pair === 'number') return;
    if (depth == 4) {
        if (leftFunc) leftFunc(pair[0]);
        if (rightFunc) rightFunc(pair[1]);

        return 1;
    }

    let l = explode(leftFunc, (v) => (typeof pair[1] === "number") ? pair[1] += v : addToLeft(pair[1], v), pair[0], depth + 1);
    if (l === 1) {
        pair[0] = 0;
        return 2;
    } else if (l === 2) {
        return 2;
    }
    let r = explode((v) => (typeof pair[0] === "number") ? pair[0] += v : addToRight(pair[0], v), rightFunc, pair[1], depth + 1);
    if (r === 1) {
        pair[1] = 0;
        return 2;
    } else if (r == 2) {
        return 2;
    }

    return 0;
}
function split(pair) {
    function stuff(ind) {
        if (typeof pair[ind] === "number") {
            if (pair[ind] > 9) {
                pair[ind] = [Math.floor(pair[ind] / 2), Math.ceil(pair[ind] / 2)];
                return true;
            }
            return false;
        } else {
            return split(pair[ind]);
        }
    }

    return stuff(0) || stuff(1);
}

function reduce(pair) {
    while (explode(null, null, pair, 0) || split(pair)) { }
}

function magnitude(pair) {
    return (typeof pair == "number") ? pair : magnitude(pair[0]) * 3 + magnitude(pair[1]) * 2;
}

function clone(arr) {
    return JSON.parse(JSON.stringify(arr));
}

export function part1() {
    let num = clone(input[0]);
    for (let i = 1; i < input.length; i++) {
        num = [num, clone(input[i])];
        reduce(num);
    }
    return magnitude(num);
}

export function part2() {
    let max = 0;
    for (let i = 0; i < input.length; i++) {
        for (let j = 0; j < input.length; j++) {
            if (i == j) continue;

            let num = clone([input[i], input[j]]);
            reduce(num);
            max = Math.max(max, magnitude(num));
        }
    }
    return max;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
