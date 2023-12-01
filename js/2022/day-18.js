import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput()).map(x => x.map(y => y + 1));
const size = 32;

export function part1() {
    const grid = new Uint8Array(size * size * size);

    function get(x, y, z) {
        return grid[x + y * size + z * size * size];
    }

    for (const [x, y, z] of input) {
        grid[x + y * size + z * size * size] = 1;
    }

    let c = 0;
    for (const [x, y, z] of input) {
        if (!get(x - 1, y, z)) c++;
        if (!get(x + 1, y, z)) c++;
        if (!get(x, y - 1, z)) c++;
        if (!get(x, y + 1, z)) c++;
        if (!get(x, y, z - 1)) c++;
        if (!get(x, y, z + 1)) c++;
    }

    return c;
}

export function part2() {
    const grid = new Uint8Array(size * size * size);

    function get(x, y, z) {
        return grid[x + y * size + z * size * size];
    }
    function set(x, y, z, v) {
        grid[x + y * size + z * size * size] = v;
    }

    let mx = 0;
    let my = 0;
    let mz = 0;
    for (const [x, y, z] of input) {
        set(x, y, z, 1);

        mx = Math.max(mx, x);
        my = Math.max(my, y);
        mz = Math.max(mz, z);
    }

    mx++;
    my++;
    mz++;

    const p = [[0, 0, 0]];
    while (p.length) {
        const [x, y, z] = p.pop();

        if (x > 0  && get(x - 1, y, z) == 0) { set(x - 1, y, z, 2); p.push([x - 1, y, z]); }
        if (x < mx && get(x + 1, y, z) == 0) { set(x + 1, y, z, 2); p.push([x + 1, y, z]); }
        if (y > 0  && get(x, y - 1, z) == 0) { set(x, y - 1, z, 2); p.push([x, y - 1, z]); }
        if (y < my && get(x, y + 1, z) == 0) { set(x, y + 1, z, 2); p.push([x, y + 1, z]); }
        if (z > 0  && get(x, y, z - 1) == 0) { set(x, y, z - 1, 2); p.push([x, y, z - 1]); }
        if (z < mz && get(x, y, z + 1) == 0) { set(x, y, z + 1, 2); p.push([x, y, z + 1]); }
    }

    let c = 0;
    for (const [x, y, z] of input) {
        if (get(x - 1, y, z) == 2) c++;
        if (get(x + 1, y, z) == 2) c++;
        if (get(x, y - 1, z) == 2) c++;
        if (get(x, y + 1, z) == 2) c++;
        if (get(x, y, z - 1) == 2) c++;
        if (get(x, y, z + 1) == 2) c++;
    }
    return c;
}

import { checkAnswers } from "../test.js";
checkAnswers();
