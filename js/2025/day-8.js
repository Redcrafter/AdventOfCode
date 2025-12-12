import { extractNumbers, getInput } from "../util.ts";

const input = extractNumbers(getInput());

export function part1() {
    const dists = [];
    const map = new Map();

    for (let i = 0; i < input.length; i++) {
        map.set(i, [i]);
    }

    for (let j = 0; j < input.length; j++) {
        const [x1, y1, z1] = input[j];

        for (let k = 0; k < j; k++) {
            const [x2, y2, z2] = input[k];

            const dist = (x1 - x2) ** 2 + (y1 - y2) ** 2 + (z1 - z2) ** 2;
            dists.push([dist, j, k]);
        }
    }

    dists.sort((a, b) => a[0] - b[0]);

    for (let i = 0; i < 1000; i++) {
        const [_, a, b] = dists[i];

        const g = [...new Set([...map.get(a), ...map.get(b)])];
        for (const item of g) {
            map.set(item, g);
        }
    }

    const asd = [...new Set([...map.values()])];
    asd.sort((a, b) => b.length - a.length);

    return asd[0].length * asd[1].length * asd[2].length;
}

export function part2() {
    const dists = [];
    const map = new Map();

    for (let i = 0; i < input.length; i++) {
        map.set(i, [i]);
    }

    for (let j = 0; j < input.length; j++) {
        const [x1, y1, z1] = input[j];

        for (let k = 0; k < j; k++) {
            const [x2, y2, z2] = input[k];

            const dist = (x1 - x2) ** 2 + (y1 - y2) ** 2 + (z1 - z2) ** 2;
            dists.push([dist, j, k]);
        }
    }

    dists.sort((a, b) => b[0] - a[0]);

    let res = 0;
    for (let i = 0; map.get(0).length < 1000; i++) {
        const [_, a, b] = dists.pop();

        res = input[a][0] * input[b][0];

        let g = [...new Set([...map.get(a), ...map.get(b)])];
        for (const item of g) {
            map.set(item, g);
        }
    }

    return res;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
