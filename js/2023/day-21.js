import { getInput } from "../util.js";

const input = getInput();

const height = input.length;
const width = input[0].length;

export function part1() {
    let positions = new Set();

    let sx = 65;
    let sy = 65;

    positions.add(sx + sy * width)

    for (let i = 0; i < 65; i++) {
        let next = new Set();

        for (const p of positions) {
            let x = p % width;
            let y = Math.floor(p / width);

            if (x > 0 && input[y][x - 1] != "#") next.add((x - 1) + (y) * width);
            if (x + 1 < width && input[y][x + 1] != "#") next.add((x + 1) + (y) * width);
            if (y > 0 && input[y - 1][x] != "#") next.add((x) + (y - 1) * width);
            if (y + 1 < height && input[y + 1][x] != "#") next.add((x) + (y + 1) * width);
        }
        positions = next;
    }

    return positions.size;
}

export function part2() {
    let positions = new Set();
    positions.add(JSON.stringify({ x: 65, y: 65 }));

    function get(x, y) {
        return input[((y % height) + height) % height][((x % width) + width) % width];
    }

    let vals = [];
    for (let i = 0; i < 65 + 131; i++) {
        let next = new Set();

        for (const p of positions) {
            let asd = JSON.parse(p);
            let x = asd.x;
            let y = asd.y;

            if (get(x - 1, y) != "#") next.add(JSON.stringify({ x: x - 1, y }));
            if (get(x + 1, y) != "#") next.add(JSON.stringify({ x: x + 1, y }));
            if (get(x, y - 1) != "#") next.add(JSON.stringify({ x, y: y - 1 }));
            if (get(x, y + 1) != "#") next.add(JSON.stringify({ x, y: y + 1 }));
        }
        if (i == 65 || i == 65 + 131) {
            vals.push(positions.size);
        }
        positions = next;
    }

    vals.push(positions.size);

    let n = (26501365 - 65) / 131;

    let delta = (vals[2] - vals[1]) - (vals[1] - vals[0]);
    let step = vals[1] - vals[0];
    let asd = vals[0];

    for (let i = 0; i < n; i++) {
        asd += step;
        step += delta;
    }

    return asd;
}

import { checkAnswers } from "../test.js";
checkAnswers();
