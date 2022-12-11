import { getInput } from "../util.js";
const input = getInput().flatMap(x => [...x].map(y => parseInt(y)));

export function part1() {
    let data = new Uint8Array(256);
    for (let y = 0; y < 10; y++) {
        for (let x = 0; x < 10; x++) {
            data[(x + 1) + (y + 1) * 16] = input[x + y * 10];
        }
    }

    let stackId = 0;
    let stack = new Uint8Array(256);
    let resetId = 0;
    let reset = new Uint8Array(256);

    let flashes = 0;

    for (let i = 0; i < 100; i++) {
        for (let y = 1; y <= 10; y++) {
            for (let x = 1; x <= 10; x++) {
                let j = x + (y << 4);
                if (data[j]++ >= 9) {
                    reset[resetId++] = j;

                    if (data[j - 1 - 16]++ == 9) stack[stackId++] = j - 1 - 16;
                    if (data[j + 0 - 16]++ == 9) stack[stackId++] = j + 0 - 16;
                    if (data[j + 1 - 16]++ == 9) stack[stackId++] = j + 1 - 16;
                    if (data[j - 1]++ == 9) stack[stackId++] = j - 1;

                    data[j + 1]++;
                    data[j - 1 + 16]++;
                    data[j + 0 + 16]++;
                    data[j + 1 + 16]++;
                }
            }
        }

        while (stackId > 0) {
            let ind = stack[--stackId];
            let x = ind & 0xF;
            let y = ind >> 4;
            if (x < 1 || x > 10 || y < 1 || y > 10) continue;

            reset[resetId++] = ind;

            if (data[ind - 1 - 16]++ == 9) stack[stackId++] = ind - 1 - 16;
            if (data[ind + 0 - 16]++ == 9) stack[stackId++] = ind + 0 - 16;
            if (data[ind + 1 - 16]++ == 9) stack[stackId++] = ind + 1 - 16;
            if (data[ind - 1]++ == 9) stack[stackId++] = ind - 1;
            if (data[ind + 1]++ == 9) stack[stackId++] = ind + 1;
            if (data[ind - 1 + 16]++ == 9) stack[stackId++] = ind - 1 + 16;
            if (data[ind + 0 + 16]++ == 9) stack[stackId++] = ind + 0 + 16;
            if (data[ind + 1 + 16]++ == 9) stack[stackId++] = ind + 1 + 16;
        }

        flashes += resetId;

        while (resetId > 0) {
            data[reset[--resetId]] = 0;
        }
    }

    return flashes;
}

export function part2() {
    let data = new Uint8Array(256);
    for (let y = 0; y < 10; y++) {
        for (let x = 0; x < 10; x++) {
            data[(x + 1) + (y + 1) * 16] = input[x + y * 10];
        }
    }

    let stackId = 0;
    let stack = new Uint8Array(256);
    let resetId = 0;
    let reset = new Uint8Array(256);

    for (let i = 0; ; i++) {
        for (let y = 1; y <= 10; y++) {
            for (let x = 1; x <= 10; x++) {
                let j = x + (y << 4);
                if (data[j]++ >= 9) {
                    reset[resetId++] = j;

                    if (data[j - 1 - 16]++ == 9) stack[stackId++] = j - 1 - 16;
                    if (data[j + 0 - 16]++ == 9) stack[stackId++] = j + 0 - 16;
                    if (data[j + 1 - 16]++ == 9) stack[stackId++] = j + 1 - 16;
                    if (data[j - 1]++ == 9) stack[stackId++] = j - 1;

                    data[j + 1]++;
                    data[j - 1 + 16]++;
                    data[j + 0 + 16]++;
                    data[j + 1 + 16]++;
                }
            }
        }

        while (stackId > 0) {
            let ind = stack[--stackId];
            let x = ind & 0xF;
            let y = ind >> 4;
            if (x < 1 || x > 10 || y < 1 || y > 10) continue;

            reset[resetId++] = ind;

            if (data[ind - 1 - 16]++ == 9) stack[stackId++] = ind - 1 - 16;
            if (data[ind + 0 - 16]++ == 9) stack[stackId++] = ind + 0 - 16;
            if (data[ind + 1 - 16]++ == 9) stack[stackId++] = ind + 1 - 16;
            if (data[ind - 1]++ == 9) stack[stackId++] = ind - 1;
            if (data[ind + 1]++ == 9) stack[stackId++] = ind + 1;
            if (data[ind - 1 + 16]++ == 9) stack[stackId++] = ind - 1 + 16;
            if (data[ind + 0 + 16]++ == 9) stack[stackId++] = ind + 0 + 16;
            if (data[ind + 1 + 16]++ == 9) stack[stackId++] = ind + 1 + 16;
        }

        if (resetId == 100) return i + 1;

        while (resetId > 0) {
            data[reset[--resetId]] = 0;
        }
    }
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
