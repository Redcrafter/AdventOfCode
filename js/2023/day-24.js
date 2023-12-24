import { getInput } from "../util.js";
import { init } from "z3-solver";

const input = getInput();

function toSlope(a, v) {
    let s = v[1] / v[0];

    return [
        a[1] - (s * a[0]),
        s
    ]
}

function intersect(p0, p1) {
    let [c, a] = toSlope(p0[0], p0[1]);
    let [d, b] = toSlope(p1[0], p1[1]);

    return [
        (d - c) / (a - b),
        a * (d - c) / (a - b) + c
    ]
}

export function part1() {
    const min = 200000000000000;
    const max = 400000000000000;

    let p = []
    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split("@");

        let pos = a.split(", ").map(x => parseInt(x));
        let vel = b.split(", ").map(x => parseInt(x));

        p.push([pos, vel]);
    }

    let result = 0;

    for (let i = 0; i < p.length; i++) {
        const a = p[i];
        for (let j = i + 1; j < p.length; j++) {
            const b = p[j];

            let [x, y] = intersect(a, b);

            if ((x - a[0][0]) / a[1][0] < 0 || (y - a[0][1]) / a[1][1] < 0) {
                continue
            }
            if ((x - b[0][0]) / b[1][0] < 0 || (y - b[0][1]) / b[1][1] < 0) {
                continue
            }
            if (x >= min && x <= max && y >= min && y <= max)
                result++;
        }
    }

    return result
}

export async function part2() {
    let p = []

    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split("@");

        let pos = a.split(", ").map(x => parseInt(x));
        let vel = b.split(", ").map(x => parseInt(x));

        p.push([pos, vel]);
    }


    const { Context, em } = await init();
    const Z3 = new Context('main');
    const solver = new Z3.Solver();

    let rpx = Z3.Int.const('rpx');
    let rpy = Z3.Int.const('rpy');
    let rpz = Z3.Int.const('rpz');

    let rvx = Z3.Int.const('rvx');
    let rvy = Z3.Int.const('rvy');
    let rvz = Z3.Int.const('rvz');

    let _t = [];
    for (let i = 0; i < 3; i++) {
        const a = p[i];

        const t = Z3.Int.const(`t${i}`);
        solver.add(t.ge(0));
        solver.add(t.mul(a[1][0]).add(a[0][0]).sub(rvx.mul(t)).eq(rpx));
        solver.add(t.mul(a[1][1]).add(a[0][1]).sub(rvy.mul(t)).eq(rpy));
        solver.add(t.mul(a[1][2]).add(a[0][2]).sub(rvz.mul(t)).eq(rpz));
        _t.push(t);
    }

    await solver.check();
    let model = solver.model();

    let result = model.get(rpx).value() +
        model.get(rpy).value() +
        model.get(rpz).value();

    console.log(model.get(rpx).value(), model.get(rpy).value(), model.get(rpz).value())
    console.log(model.get(rvx).value(), model.get(rvy).value(), model.get(rvz).value())
    console.log(model.get(_t[0]).value(), model.get(_t[1]).value(), model.get(_t[2]).value())

    em.PThread.terminateAllThreads(); // wtf z3. can you make a working api
    return Number(result);
}

import { checkAnswers } from "../test.js";
checkAnswers();
