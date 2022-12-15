import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput());

function man(x0, y0, x1, y1) {
    return Math.abs(x1 - x0) + Math.abs(y1 - y0);
}

export function part1() {
    const y = 2000000;

    let minX = Infinity;
    let maxX = -Infinity;

    for (const [x1, y1, x2, y2] of input) {
        const d = man(x1, y1, x2, y2);
        const dy = Math.abs(y1 - y);

        minX = Math.min(minX, x1 - (d - dy));
        maxX = Math.max(maxX, x1 + (d - dy));
    }

    let c = 0;
    let x = minX;

    l1: while (x < maxX) {
        for (const [x1, y1, x2, y2] of input) {
            let d1 = man(x1, y1, x2, y2);

            if (man(x1, y1, x, y) <= d1) {
                let s = Math.abs(y1 - y);
                let e = x1 + d1 - s + 1;

                if (y1 == y && x1 >= x && x1 <= e) c--; // signal on line
                if (y2 == y && x2 >= x && x2 <= e) c--; // beacon on line

                c += e - x;

                x = e;
                continue l1;
            }
        }
    }
    return c;
}

export function part2_old() {
    for (let y = 0; y <= 4000000; y++) {
        let x = 0;

        l1: while (x <= 4000000) {
            for (let i = 0; i < input.length; i++) {
                const [x1, y1, x2, y2] = input[i];
                const d1 = man(x1, y1, x2, y2);

                if (man(x1, y1, x, y) <= d1) {
                    let s = Math.abs(y1 - y);
                    x = x1 + d1 - s + 1;

                    continue l1;
                }
            }

            return x * 4000000 + y;
        }
    }
}

export function part2() {
    let p = [];

    // find pairs of diamonds which are exactly 1 space apart
    for (let i = 0; i < input.length; i++) {
        const a = input[i];
        const d1 = man(...a);

        for (let j = i + 1; j < input.length; j++) {
            const b = input[j];

            if (a == b) continue;

            const d2 = man(...b);
            const test = man(a[0], a[1], b[0], b[1]);

            if (test == d1 + d2 + 2) {
                p.push([a, b]);
            }
        }
    }
    console.assert(p.length == 2);

    // find point by intersecting center lines of both pairs
    function extractLine(a, b) {
        let _a;
        let _c;

        if (a[0] > b[0]) {
            if (a[1] > b[1]) {
                _a = -1;
                _c = a[0] + a[1] - man(...a) - 1;
            } else {
                _a = 1;
                _c = -a[0] + a[1] + man(...a) + 1;
            }
        } else {
            if (a[1] > b[1]) {
                _a = 1;
                _c = -a[0] + a[1] - man(...a) - 1;
            } else {
                _a = -1;
                _c = a[0] + a[1] + man(...a) + 1;
            }
        }

        return [_a, _c];
    }

    let [a, c] = extractLine(...p[0]);
    let [b, d] = extractLine(...p[1]);

    let x = (d - c) / (a - b);
    let y = a * x + c;

    return x * 4000000 + y;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
