import { getInput } from "../util.ts";

const input = getInput();

export function part1() {
    const map = new Map();

    for (let i = 0; i < input.length; i++) {
        const [first, asd] = input[i].split(": ");
        const stuff = asd.split(" ");

        map.set(first, stuff);
    }

    const mem = new Map();
    mem.set("out", 1);

    function visit(node) {
        if (mem.has(node)) return mem.get(node);

        let res = 0;
        for (const sub of map.get(node)) {
            res += visit(sub);
        }
        mem.set(node, res);
        return res;
    }

    return visit("you");
}

export function part2() {
    const map = new Map();

    for (let i = 0; i < input.length; i++) {
        const [first, asd] = input[i].split(": ");
        const stuff = asd.split(" ");

        map.set(first, stuff);
    }

    const mem = new Map();
    mem.set("out", [1, 0, 0]);

    function visit(node) {
        if (mem.has(node))
            return mem.get(node);

        const valid = node == "dac" || node == "fft";
        const res = [0, 0, 0];

        for (const sub of map.get(node)) {
            const asd = visit(sub);
            if(valid) {
                res[1] += asd[0];
                res[2] += asd[1];
            } else {
                res[0] += asd[0];
                res[1] += asd[1];
                res[2] += asd[2];
            }
        }
        mem.set(node, res);
        return res;
    }

    return visit("svr")[2];
}

import { checkAnswers } from "../test.ts";
checkAnswers();
