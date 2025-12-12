import { arraySplit, getInput } from "../util.ts";

const input = arraySplit(getInput().slice(1), x => x.match(/---/)).map(x => x.map(y => y.split(",").map(z => parseInt(z))));

let rotates = [
    (x, y, z) => [x, y, z], (x, y, z) => [x, y, -z], (x, y, z) => [x, -y, z], (x, y, z) => [x, -y, -z], (x, y, z) => [-x, y, z], (x, y, z) => [-x, y, -z], (x, y, z) => [-x, -y, z], (x, y, z) => [-x, -y, -z],
    (x, y, z) => [x, z, y], (x, y, z) => [x, z, -y], (x, y, z) => [x, -z, y], (x, y, z) => [x, -z, -y], (x, y, z) => [-x, z, y], (x, y, z) => [-x, z, -y], (x, y, z) => [-x, -z, y], (x, y, z) => [-x, -z, -y],
    (x, y, z) => [y, x, z], (x, y, z) => [y, x, -z], (x, y, z) => [y, -x, z], (x, y, z) => [y, -x, -z], (x, y, z) => [-y, x, z], (x, y, z) => [-y, x, -z], (x, y, z) => [-y, -x, z], (x, y, z) => [-y, -x, -z],
    (x, y, z) => [y, z, x], (x, y, z) => [y, z, -x], (x, y, z) => [y, -z, x], (x, y, z) => [y, -z, -x], (x, y, z) => [-y, z, x], (x, y, z) => [-y, z, -x], (x, y, z) => [-y, -z, x], (x, y, z) => [-y, -z, -z],
    (x, y, z) => [z, x, y], (x, y, z) => [z, x, -y], (x, y, z) => [z, -x, y], (x, y, z) => [z, -x, -y], (x, y, z) => [-z, x, y], (x, y, z) => [-z, x, -y], (x, y, z) => [-z, -x, y], (x, y, z) => [-z, -x, -y],
    (x, y, z) => [z, y, x], (x, y, z) => [z, y, -x], (x, y, z) => [z, -y, x], (x, y, z) => [z, -y, -x], (x, y, z) => [-z, y, x], (x, y, z) => [-z, y, -x], (x, y, z) => [-z, -y, x], (x, y, z) => [-z, -y, -x],
]

function findOverlap(s1, input) {
    let good = [];

    for (let i = 0; i < input.length; i++) {
        const s2 = input[i];
        if (s2 === null) continue;
        let diffs = new Map();

        for (const p1 of s1) {
            for (const p2 of s2) {
                for (let rot = 0; rot < rotates.length; rot++) {
                    let p = rotates[rot](...p2);

                    let dx = p1[0] - p[0];
                    let dy = p1[1] - p[1];
                    let dz = p1[2] - p[2];

                    let hash = (((dx + 8000) * 16000 + (dy + 8000)) * 16000 + (dz + 8000)) * 64 + rot;

                    diffs.set(hash, (diffs.get(hash) ?? 0) + 1);
                }
            }
        }

        for (let [a, b] of diffs) {
            if (b >= 12) {
                let rot = a & 63;
                a = (a - rot) / 64;

                let z = a % 16000;
                a = (a - z) / 16000;

                let y = (a % 16000);
                a = (a - y) / 16000;

                let x = a;

                good.push({
                    i,
                    rot,
                    x: x - 8000,
                    y: y - 8000,
                    z: z - 8000,
                });
            }
        }
    }

    return good;
}

export function part1() {
    let inp = input.slice();
    let total = new Set();
    let stack = [];

    function add(points) {
        stack.push(points);
        for (const d of points) {
            total.add(((d[0] + 2000) * 4000 + (d[1] + 2000)) * 4000 + (d[2] + 2000));
        }
    }

    add(inp[0]);
    inp[0] = null;

    while (stack.length > 0) {
        let el = stack.pop();
        let asdf = findOverlap(el, inp);

        for (const item of asdf) {
            let dat = inp[item.i];
            let rot = rotates[item.rot];

            let points = dat.map(x => {
                let r = rot(...x);
                return [r[0] + item.x, r[1] + item.y, r[2] + item.z];
            });

            add(points);
            inp[item.i] = null;
        }
    }

    return total.size;
}

export function part2() {
    let inp = input.slice();
    let known = [[0, 0, 0]];
    let stack = [];

    stack.push(inp[0]);
    inp[0] = null;

    while (stack.length > 0) {
        let el = stack.pop();
        let asdf = findOverlap(el, inp);

        for (const item of asdf) {
            let dat = inp[item.i];
            let rot = rotates[item.rot];

            let points = dat.map(x => {
                let r = rot(...x);
                return [r[0] + item.x, r[1] + item.y, r[2] + item.z];
            });

            known.push([item.x, item.y, item.z]);
            stack.push(points);
            inp[item.i] = null;
        }
    }

    let max = 0;
    for (const a of known) {
        for (const b of known) {
            let dist = Math.abs(a[0] - b[0]) + Math.abs(a[1] - b[1]) + Math.abs(a[2] - b[2]);

            if (dist > max) {
                max = dist;
            }
        }
    }
    return max;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
