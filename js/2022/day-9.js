import { getInput } from "../util.js";
const input = getInput();

const arrSize = 520;

function pi(str) {
    let val = 0;
    for (let i = 2; i < str.length ; i++) {
        val = val * 10 + str.charCodeAt(i) - 48
    }
    return val;
}

export function part1() {
    const grid = new Uint32Array(arrSize * arrSize);

    let hx = arrSize / 2;
    let hy = arrSize / 2;
    let tx = arrSize / 2;
    let ty = arrSize / 2;

    grid[arrSize / 2 * (1 + arrSize)] = 1;
    let res = 1;

    for (let i = 0; i < input.length; i++) {
        const a = input[i];
        const b = pi(a);

        let mx = 0
        let my = 0;

        switch (a[0]) {
            case "L": mx--; break;
            case "R": mx++; break;
            case "U": my--; break;
            case "D": my++; break;
        }

        for (let i = 0; i < b; i++) {
            hx += mx;
            hy += my;

            const dx = hx - tx;
            const dy = hy - ty;

            const ax = Math.abs(dx);
            const ay = Math.abs(dy);

            if (ax >= 1 && ay > 1 || ax > 1 && ay >= 1) {
                tx += Math.sign(dx);
                ty += Math.sign(dy);
            } else if (ax > 1) {
                tx += Math.sign(dx);
            } else if (ay > 1) {
                ty += Math.sign(dy);
            } else {
                continue
            }

            if (grid[tx + ty * arrSize] == 0) {
                res++;
                grid[tx + ty * arrSize] = 1;
            }
        }
    }

    return res;
}

export function part2() {
    const grid = new Uint8Array(arrSize * arrSize);

    const nodes = [];
    for (let i = 0; i < 10; i++) {
        nodes.push([arrSize / 2, arrSize / 2]);
    }

    grid[arrSize / 2 * (1 + arrSize)] = 1;
    let res = 1;

    for (let i = 0; i < input.length; i++) {
        let a = input[i];
        let b = pi(a);

        let mx = 0
        let my = 0;

        switch (a[0]) {
            case "L": mx--; break;
            case "R": mx++; break;
            case "U": my--; break;
            case "D": my++; break;
        }

        loop: for (let j = 0; j < b; j++) {
            let last = nodes[0];
            last[0] += mx;
            last[1] += my;

            for (let k = 1; k < 10; k++) {
                const n = nodes[k];

                const dx = last[0] - n[0];
                const dy = last[1] - n[1];

                const ax = Math.abs(dx);
                const ay = Math.abs(dy);

                if (ax >= 1 && ay > 1 || ax > 1 && ay >= 1) {
                    n[0] += Math.sign(dx);
                    n[1] += Math.sign(dy);
                } else if (ax > 1) {
                    n[0] += Math.sign(dx);
                } else if (ay > 1) {
                    n[1] += Math.sign(dy);
                } else {
                    continue loop;
                }
                last = n;
            }

            if (grid[nodes[9][0] + nodes[9][1] * arrSize] == 0) {
                res++;
                grid[nodes[9][0] + nodes[9][1] * arrSize] = 1;
            }
        }
    }

    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
