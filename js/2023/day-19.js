import { arraySplit, getInput } from "../util.js";

const input = arraySplit(getInput(false), x => x.length == 0)

export function part1() {
    let res = 0;

    let [a, b] = input;

    let asd = new Map();

    for (let i = 0; i < a.length; i++) {
        const line = a[i].match(/(\w+)\{(.+)\}/);

        const rules = line[2].split(",").map(x => x.split(":"));

        asd.set(line[1], rules);
    }
    function check(part) {
        let x, a, m, s;

        for (const [k, v] of part) {
            if (k == "x") x = parseInt(v);
            if (k == "a") a = parseInt(v);
            if (k == "m") m = parseInt(v);
            if (k == "s") s = parseInt(v);
        }

        let cr = "in";
        while (true) {
            if (cr == "A") {
                return x + a + m + s;
            } else if (cr == "R") {
                return 0;
            }

            let r = asd.get(cr);

            for (const dd of r) {
                if (dd.length == 1) {
                    cr = dd[0];
                    break;
                } else {
                    if (eval(dd[0])) {
                        cr = dd[1];
                        break;
                    }
                }
            }

        }
    }

    for (let i = 0; i < b.length; i++) {
        const part = b[i].replace(/{|}/g, "").split(",").map(x => x.split("="));

        res += check(part)
    }

    return res;
}

export function part2() {
    let [a, b] = input;

    let asd = new Map();

    for (let i = 0; i < a.length; i++) {
        const line = a[i].match(/(\w+)\{(.+)\}/);

        const rules = line[2].split(",").map(x => x.split(":"));

        asd.set(line[1], rules);
    }

    function count(rule, part) {
        if (rule == "A") {
            return (part.x[1] - part.x[0] + 1) *
                (part.m[1] - part.m[0] + 1) *
                (part.a[1] - part.a[0] + 1) *
                (part.s[1] - part.s[0] + 1);
        } else if (rule == "R") {
            return 0;
        }

        let r = asd.get(rule);

        let c = 0;
        for (const dd of r) {
            if (dd.length == 1) {
                c += count(dd[0], part);
            } else {
                let n = parseInt(dd[0].substring(2));
                let ra = part[dd[0][0]];

                let left, right;

                if (dd[0][1] == "<") {
                    left = ra[0];
                    right = n - 1;
                    part[dd[0][0]][0] = n;
                } else {
                    left = n + 1;
                    right = ra[1];
                    part[dd[0][0]][1] = n;
                }

                // (left > right) never happens so whatever

                let asd = { x: part.x.slice(), m: part.m.slice(), a: part.a.slice(), s: part.s.slice() };
                asd[dd[0][0]] = [left, right];
                c += count(dd[1], asd);
            }
        }
        return c;
    }

    return count("in", { x: [1, 4000], m: [1, 4000], a: [1, 4000], s: [1, 4000] });
}

import { checkAnswers } from "../test.js";
checkAnswers();
