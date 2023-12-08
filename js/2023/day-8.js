import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    let inst = input[0];
    let map = new Map();

    for (let i = 1; i < input.length; i++) {
        const [id, left, right] = input[i].match(/\w{3}/g);
        map.set(id, [left, right]);
    }

    let pos = "AAA";
    let i = 0;
    while (pos != "ZZZ") {
        let dir = inst[(i++) % inst.length];
        let m = map.get(pos);
        if (dir == "R") {
            pos = m[1];
        } else {
            pos = m[0];
        }
    }

    return i;
}

function gcd(a, b) {
    while (b != 0) {
        let t = b;
        b = a % b;
        a = t;
    }
    return a;
}

function lcm(a, b) {
    return Math.abs(a) * (Math.abs(b) / gcd(a, b));
}

export function part2() {
    let inst = input[0];

    let map = new Map();
    let pos = [];

    for (let i = 1; i < input.length; i++) {
        const [id, left, right] = input[i].match(/\w{3}/g);
        map.set(id, [left, right]);

        if (id[2] == "A") {
            pos.push(id);
        }
    }

    let result = 1;
    for (let i = 0; i < pos.length; i++) {
        let p = pos[i];

        let j = 0;
        while (p[2] != "Z") {
            p = map.get(p)[inst[(j++) % inst.length] == "L" ? 0 : 1];
        }
        // input is formatted nicely so this just works
        result = lcm(j, result);
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
