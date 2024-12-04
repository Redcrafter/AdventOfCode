import { getInput } from "../util.js";

const input = getInput().map(x => new Uint8Array([...x].map(x => x.charCodeAt(0))));
console.assert(input.length == input[0].length);

export function part1() {
    let result = 0;
    const h = input.length;
    const w = input[0].length;

    for (let y = 0; y < h; y++) {
        let v1 = 0, v2 = 0;
        for (let x = 0; x < w; x++) {
            v1 = (v1 << 8) | input[y][x];
            v2 = (v2 << 8) | input[x][y];
            result += (v1 == 1396788568) + (v1 == 1481458003) + (v2 == 1396788568) + (v2 == 1481458003);
        }
    }

    const w1 = w - 1;
    for (let i = 0; i < w - 3; i++) {
        let vx = 0, vy = 0;
        for (let j = 0; j < (w - i); j++) {
            vx = (vx << 8) | input[i + j][j];
            result += vx == 1396788568;
            result += vx == 1481458003;

            vy = (vy << 8) | input[w1 - i - j][j];
            result += vy == 1396788568;
            result += vy == 1481458003;
        }
    }

    for (let i = 1; i < w - 3; i++) {
        let vx = 0, vy = 0;
        for (let j = 0; j < w - i; j++) {
            vx = (vx << 8) | input[j][i + j];
            result += vx == 1396788568;
            result += vx == 1481458003;

            vy = (vy << 8) | input[w1 - j][i + j];
            result += vy == 1396788568;
            result += vy == 1481458003;
        }
    }

    return result;
}

export function part2() {
    let result = 0;

    const h = input.length - 1;
    const w = input[0].length - 1;

    for (let y = 1; y < h; y++) {
        for (let x = 1; x < w; x++) {
            if (input[y][x] === 65) {
                const tl = input[y - 1][x - 1];
                const tr = input[y - 1][x + 1];
                const bl = input[y + 1][x - 1];
                const br = input[y + 1][x + 1];
                const v = tl | (bl << 8) | (tr << 16) | (br << 24);
                result += (v == 1397968205) + (v == 1397576525) + (v == 1296913235) + (v == 1297304915);
            }
        }
    }
    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
