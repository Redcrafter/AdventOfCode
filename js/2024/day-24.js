import { getInput } from "../util.js";

const input = getInput();
const input1 = input.slice(0, 90);
const input2 = input.slice(90);

export function part1() {
    const known = new Map();
    for (const line of input1) {
        const [a, b] = line.split(": ");
        known.set(a, parseInt(b));
    }

    const map = new Map();
    for (const line of input2) {
        const m = [...line.matchAll(/^(\w+) (\w+) (\w+) -> (\w+)$/g)][0];
        map.set(m[4], m);
    }

    function calcVal(v) {
        if (known.has(v)) return known.get(v);

        const el = map.get(v);
        const a = el[1];
        const op = el[2];
        const b = el[3];

        const av = calcVal(a);
        const bv = calcVal(b);

        let res = 0;
        switch (op) {
            case "AND": res = av & bv; break;
            case "OR": res = av | bv; break;
            case "XOR": res = av ^ bv; break;
        }
        known.set(v, res);
        return res;
    }

    let res = 0n;
    for (let i = 0; i <= 45; i++) {
        res |= BigInt(calcVal("z" + i.toString().padStart(2, "0"))) << BigInt(i);
    }
    return Number(res);
}

function part2_test(input2) {
    const i2 = input2.map(x => [...x.matchAll(/^(\w+) (\w+) (\w+) -> (\w+)$/g)][0]);

    const map = new Map()
    const map2 = new Map();
    for (const line of i2) {
        const a = line[1];
        const op = line[2];
        const b = line[3];
        const o = line[4];

        map.set(o, `${a} ${op} ${b}`);
        map2.set(`${a} ${op} ${b}`, o);
    }

    function iToStr(i) {
        return i.toString().padStart(2, "0");
    }

    function find(a, op, b) {
        const v = map2.get(`${a} ${op} ${b}`);
        if (!v) {
            return map2.get(`${b} ${op} ${a}`);
        }
        return v;
    }

    function findFullAddr(a, b, carry) {
        const xor1 = find(a, "XOR", b);
        const xor2 = find(xor1, "XOR", carry);

        const carry1 = find(a, "AND", b);
        const carry2 = find(xor1, "AND", carry);
        const carry3 = find(carry1, "OR", carry2);

        return [xor2 ?? xor1, carry3 ?? carry1];
    }

    function swap(a, b) {
        const a1 = map.get(a);
        const b1 = map.get(b);
        map.set(a, b1);
        map.set(b, a1);
        map2.set(a1, b);
        map2.set(b1, a);
    }

    const swaps = [];

    function trySwap(i, a, b, cin) {
        swaps.push([a, b]);
        swap(a, b);
        if (test(i, cin)) {
            return true;
        }
        swap(a, b);
        swaps.pop();

        return false;
    }

    function test(i, cin) {
        if (i == 45) return true;

        let [out, cout] = findFullAddr("x" + iToStr(i), "y" + iToStr(i), cin);

        const key = "z" + iToStr(i);
        if (out == key) {
            return test(i + 1, cout);
        }
        if (swaps.length == 4) return false;

        if (trySwap(i, key, out, cin)) return true;
        if (trySwap(i, out, cout, cin)) return true;

        return false;
    }

    test(0, null);
    // if (!result) throw new Error("failed to find solution");

    return swaps;
}
export function part2() {
    return part2_test(input2).flatMap(x => x).sort().join(",")
}

import { checkAnswers } from "../test.js";
checkAnswers();
