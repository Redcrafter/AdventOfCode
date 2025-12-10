import { extractNumbers, getInput } from "../util.js";
import { init } from "z3-solver";

const { Context } = await init();
const Z3 = new Context('main');

const input = getInput();

export function part1() {
    let res = 0;

    const known = new Uint8Array(1 << 10);

    function check(target, moves) {
        known.fill(0);
        known[0] = 1;

        let curr = [0];
        for (let i = 1; ; i++) {
            const next = [];

            for (const state of curr) {
                for (const move of moves) {
                    const val = state ^ move;

                    if(val == target) return i;

                    if (!known[val]) {
                        known[val] = 1;
                        next.push(val);
                    }
                }
            }
            curr = next;
        }
    }

    for (let i = 0; i < input.length; i++) {
        const line = input[i].split(" ");
        const target_ = line[0].slice(1, -1);
        const moves = line.slice(1, -1).map(x => extractNumbers(x).reduce((p, c) => p | (1 << c), 0));

        let target = 0;
        for (let i = 0; i < target_.length; i++) {
            if (target_[i] == '#') target |= 1 << i;
        }

        res += check(target, moves);
    }

    return res;
}

export async function part2() {
    let res = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i].split(" ");

        const target = extractNumbers(line.at(-1));
        const moves = line.slice(1, -1).map(x => {
            const res = new Array(target.length);
            res.fill(0);
            for (const n of extractNumbers(x)) {
                res[n] = 1;
            }
            return res;
        });

        const opt = new Z3.Optimize();

        const vars = [];
        for (let i = 0; i < moves.length; i++) {
            const v = Z3.Int.const(`n${i}`);
            vars.push(v);
            opt.add(v.ge(0));
        }

        for (let i = 0; i < target.length; i++) {
            opt.add(Z3.Sum(...vars.filter((x, j) => moves[j][i] == 1)).eq(target[i]));
        }

        const exp = Z3.Sum(...vars);
        opt.minimize(exp);
        await opt.check();
        const model = opt.model();

        res += Number(model.eval(exp));
    }

    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
