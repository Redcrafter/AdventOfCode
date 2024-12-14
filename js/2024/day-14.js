import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput());
const width = 101;
const height = 103;

export function part1() {

    let tl = 0;
    let tr = 0;
    let bl = 0;
    let br = 0;

    for (let i = 0; i < input.length; i++) {
        let [px, py, vx, vy] = input[i];

        px = (((px + vx * 100) % width) + width) % width;
        py = (((py + vy * 100) % height) + height) % height;

        if (px < 50 && py < 51) tl++;
        if (px > 50 && py < 51) tr++;
        if (px < 50 && py > 51) bl++;
        if (px > 50 && py > 51) br++;
    }
    return tl * tr * bl * br;
}

const arr = new Uint8Array(103);
export function part2() {

    let mod_w = [-1, Infinity];
    let mod_h = [-1, Infinity];
    for (let i = 0; i < width; i++) {
        arr.fill(0);

        for (const el of input) {
            arr[(((el[0] + el[2] * i) % width) + width) % width] = 1;
        }

        let sum = 0;
        for (let j = 0; j < width; j++) sum += arr[j];
        if (sum < mod_w[1]) {
            mod_w = [i, sum];
        }
    }
    for (let i = 0; i < height; i++) {
        arr.fill(0);
        for (const el of input) {
            arr[(((el[1] + el[3] * i) % height) + height) % height] = 1;
        }
        let sum = 0;
        for (let j = 0; j < height; j++) sum += arr[j];
        if (sum < mod_h[1]) {
            mod_h = [i, sum];
        }
    }

    return ((mod_w[0] * height * 51) + (mod_h[0] * width * 51)) % (width * height);

    /*
    let mod_w = [-1, Infinity];
    let mod_h = [-1, Infinity];
    for (let i = 0; i < width; i++) {
        let s = new Set();
        for (const el of input) {
            s.add((((el[0] + el[2] * i) % width) + width) % width);
        }
        if (s.size < mod_w[1]) {
            mod_w = [i, s.size];
        }
    }
    for (let i = 0; i < height; i++) {
        let s = new Set();
        for (const el of input) {
            s.add((((el[1] + el[3] * i) % height) + height) % height);
        }
        if (s.size < mod_h[1]) {
            mod_h = [i, s.size];
        }
    }

    return ((mod_w[0] * height * 51) + (mod_h[0] * width * 51)) % (width * height);
    */

    /*
    let inp = structuredClone(input);

    const grid = new Uint8Array(width * height);
    for (let i = 1; ; i++) {
        grid.fill(0);

        for (let i = 0; i < inp.length; i++) {
            let [px, py, vx, vy] = inp[i];

            px = (((px + vx) % width) + width) % width;
            py = (((py + vy) % height) + height) % height;

            inp[i][0] = px;
            inp[i][1] = py;

            grid[px + py * width] = 1;
        }

        let streak = 0;
        for (let j = 0; j < grid.length; j++) {
            if (grid[j]) {
                streak++;

                if (streak == 10) {
                    // for (let y = 0; y < height; y++) {
                    //     let line = "";
                    //     for (let x = 0; x < width; x++) {
                    //         if (grid[x + y * width]) {
                    //             line += "#";
                    //         } else {
                    //             line += " ";
                    //         }
                    //     }
                    //     console.log(line);
                    // }
                    return i;
                }
            } else {
                streak = 0;
            }
        }
    }*/
}

import { checkAnswers } from "../test.js";
checkAnswers();
