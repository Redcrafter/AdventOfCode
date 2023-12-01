import { getInput } from "../util.js";

const input = getInput().map(x => {
    let m = x.match(/(on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+)/);
    return [m[1], ...m.slice(2).map(y => parseInt(y))]
});

export function part1() {
    let cubes = [];
    for (let z = 0; z < 101; z++) {
        let row = [];
        for (let y = 0; y < 101; y++) {
            row[y] = new Array(101).fill(0);
        }
        cubes[z] = row;
    }

    for (let [s, x1, x2, y1, y2, z1, z2] of input) {
        let val = s == "on";

        x1 = Math.max(-50, x1);
        y1 = Math.max(-50, y1);
        z1 = Math.max(-50, z1);

        x2 = Math.min(50, x2);
        y2 = Math.min(50, y2);
        z2 = Math.min(50, z2);

        for (let z = z1; z <= z2; z++) {
            for (let y = y1; y <= y2; y++) {
                for (let x = x1; x <= x2; x++) {
                    cubes[z + 50][y + 50][x + 50] = val;
                }
            }
        }
    }

    let count = 0;
    for (let z = 0; z < 101; z++) {
        for (let y = 0; y < 101; y++) {
            for (let x = 0; x < 101; x++) {
                count += cubes[z][y][x];
            }
        }
    }
    return count;
}

function collides(a, b) {
    return a.x1 < b.x2 && a.x2 > b.x1 &&
        a.y1 < b.y2 && a.y2 > b.y1 &&
        a.z1 < b.z2 && a.z2 > b.z1;
}

// cuts b out of a
function cut(a, b) {
    let ret = [];

    let x1 = Math.max(a.x1, b.x1);
    let x2 = Math.min(a.x2, b.x2);

    let y1 = Math.max(a.y1, b.y1);
    let y2 = Math.min(a.y2, b.y2);

    let z1 = Math.max(a.z1, b.z1);
    let z2 = Math.min(a.z2, b.z2);

    if (x1 > a.x1) ret.push({
        x1: a.x1, x2: x1,
        y1: a.y1, y2: a.y2,
        z1: a.z1, z2: a.z2
    });
    if (x2 < a.x2) ret.push({
        x1: x2, x2: a.x2,
        y1: a.y1, y2: a.y2,
        z1: a.z1, z2: a.z2
    });

    if (y1 > a.y1) ret.push({
        x1, x2,
        y1: a.y1, y2: y1,
        z1: a.z1, z2: a.z2
    });
    if (y2 < a.y2) ret.push({
        x1, x2,
        y1: y2, y2: a.y2,
        z1: a.z1, z2: a.z2
    });

    if (z1 > a.z1) ret.push({
        x1, x2,
        y1, y2,
        z1: a.z1, z2: z1
    });
    if (z2 < a.z2) ret.push({
        x1, x2, y1, y2,
        z1: z2, z2: a.z2
    });

    return ret;
}

export function part2() {
    let areas = [];

    function add(cube, start, end) {
        for (let i = start; i < end; i++) {
            const other = areas[i];
            if (collides(other, cube)) {
                for (const item of cut(cube, other)) {
                    add(item, i + 1, end);
                }
                return;
            }
        }
        areas.push(cube);
    }
    function remove(c) {
        let len = areas.length;
        for (let i = 0; i < len; i++) {
            let other = areas[i];
            if (!collides(c, other)) continue;

            areas.splice(i, 1);
            i--;
            len--;

            areas.push(...cut(other, c));
        }
    }

    for (const [s, x1, x2, y1, y2, z1, z2] of input) {
        let cube = { x1, x2, y1, y2, z1, z2 };

        cube.x2 += 1;
        cube.y2 += 1;
        cube.z2 += 1;

        if (s === "on") {
            add(cube, 0, areas.length);
        } else {
            remove(cube);
        }
    }

    let count = 0;
    for (const c of areas) {
        count += (c.x2 - c.x1) * (c.y2 - c.y1) * (c.z2 - c.z1);
    }
    return count;
}

import { checkAnswers } from "../test.js";
checkAnswers();
