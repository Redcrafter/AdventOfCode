import { getInput, pi } from "../util.js";
let input = getInput();

const arrSize = 520;

export function part1() {
    let grid = new Uint8Array(arrSize * arrSize);

    let hx = arrSize / 2;
    let hy = arrSize / 2;
    let tx = arrSize / 2;
    let ty = arrSize / 2;

    for (let i = 0; i < input.length; i++) {
        let a = input[i];
        let b = pi(a, 2);

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

            let dx = hx - tx;
            let dy = hy - ty;

            if (Math.abs(dx) == 1 && Math.abs(dy) > 1 || Math.abs(dx) > 1 && Math.abs(dy) == 1) {
                tx += Math.sign(dx);
                ty += Math.sign(dy);
            } else if (Math.abs(dx) > 1) {
                tx += Math.sign(dx);
            } else if (Math.abs(dy) > 1) {
                ty += Math.sign(dy);
            }

            grid[tx + ty * arrSize] = 1;
        }

    }
    let res = 0;

    for (let i = 0; i < grid.length; i++) {
        res += grid[i];
    }

    return res;
}

export function part2() {
    let grid = new Uint8Array(arrSize * arrSize);

    let nodes = [];
    for (let i = 0; i < 10; i++) {
        nodes.push([arrSize / 2, arrSize / 2]);
    }
    grid[arrSize / 2 * (1 + arrSize)] = 1;

    for (let i = 0; i < input.length; i++) {
        let a = input[i];
        let b = pi(a, 2);

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
                let n = nodes[k];

                let dx = last[0] - n[0];
                let dy = last[1] - n[1];

                if (Math.abs(dx) >= 1 && Math.abs(dy) > 1 || Math.abs(dx) > 1 && Math.abs(dy) >= 1) {
                    n[0] += Math.sign(dx);
                    n[1] += Math.sign(dy);
                } else if (Math.abs(dx) > 1) {
                    n[0] += Math.sign(dx);
                } else if (Math.abs(dy) > 1) {
                    n[1] += Math.sign(dy);
                } else {
                    continue loop;
                }
                last = n;
            }

            grid[nodes[9][0] + nodes[9][1] * arrSize] = 1;
        }
    }

    let res = 0;
    for (let i = 0; i < grid.length; i++) {
        res += grid[i];
    }
    return res;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 5981);
    console.assert(part2() == 2352);
}
