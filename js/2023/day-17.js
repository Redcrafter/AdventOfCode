import { getInput } from "../util.ts";
import { Heap } from 'heap-js';

const input = getInput().map(x => [...x].map(y => parseInt(y)));

const width = input[0].length;
const height = input.length;

const up = 0;
const down = 1;
const left = 2;
const right = 3;

function rotLeft(d) {
    if (d == left) return down;
    if (d == right) return up;
    if (d == up) return left;
    if (d == down) return right;
}
function rotRight(d) {
    if (d == left) return up;
    if (d == right) return down;
    if (d == up) return right;
    if (d == down) return left;
}
function fromDir(d) {
    if (d == left) return [-1, 0];
    if (d == right) return [1, 0];
    if (d == up) return [0, -1];
    if (d == down) return [0, 1];
}

function slove(p1) {
    let heap = new Heap((a, b) => a.dist - b.dist);

    let seen = new Set();

    const start = p1 ? 1 : 4;
    const end = p1 ? 3 : 10;

    function asd(x, y, dist, dir) {
        let [dx, dy] = fromDir(dir);
        x += dx;
        y += dy;

        for (let i = 1; i < start; i++) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                continue;

            dist += input[y][x];
            x += dx;
            y += dy;
        }

        for (let i = start; i <= end; i++) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                continue;

            dist += input[y][x];
            heap.push({ dist, x, y, dir });
            x += dx;
            y += dy;
        }
    }

    asd(0, 0, 0, down);
    asd(0, 0, 0, right);

    while (heap.length != 0) {
        let el = heap.pop();

        if (el.x == width - 1 && el.y == height - 1) {
            return el.dist;
        }

        let k = `${el.x}_${el.y}_${el.dir}_${el.straight}`;
        if (seen.has(k))
            continue;
        seen.add(k);

        asd(el.x, el.y, el.dist, rotLeft(el.dir));
        asd(el.x, el.y, el.dist, rotRight(el.dir));
    }
}

export function part1() {
    return slove(true);
}

export function part2() {
    return slove(false);
}

import { checkAnswers } from "../test.ts";
checkAnswers();
