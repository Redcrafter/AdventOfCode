import { extractNumbers, getInput } from "../util.js";
const input = getInput();

const _stacks = [];
for (let i = 0; i < 9; i++) {
    let stack = [];

    for (let j = 0; j < 8; j++) {
        let c = input[j][i * 4 + 1];

        if (c != " ") {
            stack.push(c.charCodeAt(0));
        }
    }
    _stacks.push(stack.reverse());
}
const moves = extractNumbers(input.slice(9));

/** @returns {number[][]} */
function copyStack() {
    let res = new Array(_stacks.length);
    for (let i = 0; i < _stacks.length; i++) {
        res[i] = _stacks[i].slice(0);
    }
    return res;
}

export function part1() {
    let stacks = copyStack();

    for (let j = 0; j < moves.length; j++) {
        const [c, a, b] = moves[j];

        let sa = stacks[a - 1];
        let sb = stacks[b - 1];

        for (let i = 0; i < c; i++) {
            sb.push(sa[sa.length - 1]);
            sa.pop();
        }
    }

    return String.fromCharCode(...stacks.map(x => x.at(-1)));
}

export function part2() {
    let stacks = copyStack();

    for (let j = 0; j < moves.length; j++) {
        const [c, a, b] = moves[j];

        let sa = stacks[a - 1];
        let sb = stacks[b - 1];

        for (let i = 0; i < c; i++) {
            sb.push(sa[sa.length - c + i]);
        }
        for (let i = 0; i < c; i++) {
            sa.pop();
        }
    }

    return String.fromCharCode(...stacks.map(x => x.at(-1)));
}

import { checkAnswers } from "../test.js";
checkAnswers();
