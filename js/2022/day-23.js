import { getInput } from "../util.js";

const input = getInput();
const hash = "#".charCodeAt(0);

export function part1() {
    const h = Math.floor(input.length / 2);

    const size = input.length * 2;
    const sh = input.length;
    const grid = new Uint8Array(size * size);

    const elves = [];

    for (let y = 0; y < input.length; y++) {
        let line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line.charCodeAt(x) == hash) {
                let id = (x + sh - h) + (y + sh - h) * size;

                grid[id] = 1;
                elves.push(id);
            }
        }
    }

    const elfCount = elves.length;
    const dirs = new Uint32Array(elfCount);
    const consider = new Uint8Array(size * size);

    let minX = Infinity;
    let maxX = 0;
    let minY = Infinity;
    let maxY = 0;

    let m0 = 0b000_000_111;
    let m1 = 0b111_000_000;
    let m2 = 0b001_001_001;
    let m3 = 0b100_100_100;

    let p0 = -size;
    let p1 = size;
    let p2 = -1;
    let p3 = 1;

    for (let i = 0; i < 10; i++) {
        for (let k = 0; k < elfCount; k++) {
            const el = elves[k];

            const NW = grid[el - 1 - size];
            const N = grid[el - size];
            const NE = grid[el + 1 - size];
            const W = grid[el - 1];
            const E = grid[el + 1];
            const SW = grid[el - 1 + size];
            const S = grid[el + size];
            const SE = grid[el + 1 + size];

            const val = NW | N << 1 | NE << 2 | W << 3 | E << 5 | SW << 6 | S << 7 | SE << 8;

            dirs[k] = 0;
            if (val == 0) continue;

            if (!(val & m0)) {
                const key = el + p0;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m1)) {
                const key = el + p1;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m2)) {
                const key = el + p2;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m3)) {
                const key = el + p3;
                consider[key]++;
                dirs[k] = key;
            }
        }

        [m0, m1, m2, m3] = [m1, m2, m3, m0];
        [p0, p1, p2, p3] = [p1, p2, p3, p0];

        for (let k = 0; k < elfCount; k++) {
            const el = elves[k];
            const dir = dirs[k];

            if (dir != 0 && consider[dir] == 1) {
                grid[el] = 0;
                grid[dir] = 1;

                elves[k] = dir;

                const dx = dir % size;
                const dy = Math.floor(dir / size);
                minX = Math.min(minX, dx);
                maxX = Math.max(maxX, dx);
                minY = Math.min(minY, dy);
                maxY = Math.max(maxY, dy);
            }
            consider[dir] = 0;
        }
    }

    return (maxX - minX + 1) * (maxY - minY + 1) - elfCount;
}

export function part2() {
    const size = input.length * 3;
    const sh = Math.floor(size / 2);

    const grid = new Uint8Array(size * size);
    const h = Math.floor(input.length / 2);

    const elves = [];

    for (let y = 0; y < input.length; y++) {
        const line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line.charCodeAt(x) == hash) {
                let id = (x + sh - h) + (y + sh - h) * size;

                grid[id] = 1;
                elves.push(id);
            }
        }
    }

    const elfCount = elves.length;
    const dirs = new Uint32Array(elfCount);
    const consider = new Uint8Array(size * size);

    let m0 = 0b000_000_111;
    let m1 = 0b111_000_000;
    let m2 = 0b001_001_001;
    let m3 = 0b100_100_100;

    let p0 = -size;
    let p1 = size;
    let p2 = -1;
    let p3 = 1;

    let i = 0;
    while (true) {
        for (let k = 0; k < elfCount; k++) {
            const el = elves[k];

            const NW = grid[el - 1 - size];
            const N = grid[el - size];
            const NE = grid[el + 1 - size];
            const W = grid[el - 1];
            const E = grid[el + 1];
            const SW = grid[el - 1 + size];
            const S = grid[el + size];
            const SE = grid[el + 1 + size];

            const val = NW | N << 1 | NE << 2 | W << 3 | E << 5 | SW << 6 | S << 7 | SE << 8;

            dirs[k] = 0;
            if (val == 0) continue;

            if (!(val & m0)) {
                const key = el + p0;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m1)) {
                const key = el + p1;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m2)) {
                const key = el + p2;
                consider[key]++;
                dirs[k] = key;
            } else if (!(val & m3)) {
                const key = el + p3;
                consider[key]++;
                dirs[k] = key;
            }
        }

        [m0, m1, m2, m3] = [m1, m2, m3, m0];
        [p0, p1, p2, p3] = [p1, p2, p3, p0];

        let moved = false;
        for (let k = 0; k < elfCount; k++) {
            const el = elves[k];
            const dir = dirs[k];

            if (dir != 0 && consider[dir] == 1) {
                grid[el] = 0;
                grid[dir] = 1;

                elves[k] = dir;
                moved = true;
            }
            consider[dir] = 0;
        }

        i++;
        if (!moved) {
            break;
        }
    }

    return i;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
