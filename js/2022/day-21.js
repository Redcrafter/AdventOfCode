import { getInput } from "../util.js";

const input = getInput().map(x => {
    let [a, b] = x.split(": ");
    let s = b.split(" ");
    if (s.length == 1) {
        s[0] = parseInt(s[0]);
    }
    return [a, s];
});

export function part1() {
    let map = new Map(input); // makeing map takes over half the time

    function getEq(name) {
        let el = map.get(name);

        if (el.length == 1) return el[0];

        if (el[1] == "+") return getEq(el[0]) + getEq(el[2]);
        if (el[1] == "-") return getEq(el[0]) - getEq(el[2]);
        if (el[1] == "*") return getEq(el[0]) * getEq(el[2]);
        if (el[1] == "/") return getEq(el[0]) / getEq(el[2]);

        return null;
    }

    return getEq("root");
}

class Eq {
    constructor(m, b) {
        this.m = m;
        this.b = b;
    }

    add(other) {
        this.m += other.m;
        this.b += other.b;
        return this;
    }
    sub(other) {
        this.m -= other.m;
        this.b -= other.b;
        return this;
    }
    mul(other) {
        this.m = this.m * other.b + other.m * this.b;
        this.b *= other.b;
        return this;
    }
    div(other) {
        if (other.m) throw new Error();

        this.m /= other.b;
        this.b /= other.b;
        return this;
    }
}

export function part2() {
    let map = new Map(input);

    function getEq(name) {
        if (name == "humn") return new Eq(1, 0);
        let el = map.get(name);

        if (el.length == 1) return new Eq(0, el[0]);

        if (el[1] == "+") return getEq(el[0]).add(getEq(el[2]));
        if (el[1] == "-") return getEq(el[0]).sub(getEq(el[2]));
        if (el[1] == "*") return getEq(el[0]).mul(getEq(el[2]));
        if (el[1] == "/") return getEq(el[0]).div(getEq(el[2]));

        return null;
    }

    let root = map.get("root");
    let a = getEq(root[0]);
    let b = getEq(root[2]);
    let test = a.sub(b);

    return -test.b / test.m;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
