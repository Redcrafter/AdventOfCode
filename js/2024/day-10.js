import { getInput } from "../util.ts";

const input_ = getInput();
const input = new Uint8Array([...input_.join("")].map(x => parseInt(x)));

const height = input_.length;
const width = input_[0].length;

function count1(x, y, h, visited) {
    if (x < 0 || x >= width || y < 0 || y >= height) return 0;
    if (input[x + y * width] != h) return 0;
    if (visited[x + y * width]) return 0;

    visited[x + y * width] = 1;
    if (h == 9) {
        return 1;
    }

    return count1(x - 1, y, h + 1, visited) +
        count1(x + 1, y, h + 1, visited) +
        count1(x, y + 1, h + 1, visited) +
        count1(x, y - 1, h + 1, visited);
}

export function part1() {
    let result = 0;
    const visited = new Uint8Array(width * height);

    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (input[x + y * width] == 0) {
                visited.fill(0);
                result += count1(x, y, 0, visited);
            }
        }
    }

    return result;
}

function count2(x, y, h, known) {
    if (x < 0 || x >= width || y < 0 || y >= height) return 0;
    if (input[x + y * width] != h) return 0;
    if (h == 9) return 1;
    if (known[x + y * width] != -1) return known[x + y * width];

    const result = count2(x - 1, y, h + 1, known) +
        count2(x + 1, y, h + 1, known) +
        count2(x, y + 1, h + 1, known) +
        count2(x, y - 1, h + 1, known);
    known[x + y * width] = result;
    return result;
}

export function part2() {
    let result = 0;
    const known = new Int8Array(width * height);
    known.fill(-1);

    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (input[x + y * width] == 0) {
                result += count2(x, y, 0, known);
            }
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
