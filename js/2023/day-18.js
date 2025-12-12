import { getInput } from "../util.ts";

const input = getInput();

export function part1() {
    let m = 0;

    let x = 0;
    let y = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i].match(/(.) (\d+) \(#(.{6})\)/);

        let dist = parseInt(line[2]);

        let lx = x;
        let ly = y;

        if (line[1] == "L") {
            x -= dist;
        } else if (line[1] == "R") {
            x += dist;
        } else if (line[1] == "U") {
            y -= dist;
        } else if (line[1] == "D") {
            y += dist;
        }
        m += (ly + y) * (lx - x) + Math.abs(x - lx) + Math.abs(y - ly);
    }

    return m / 2 + 1;
}

export function part2() {
    let m = 0;

    let x = 0;
    let y = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i].match(/(.) (\d+) \(#(.{6})\)/);

        let dist = parseInt("0x" + line[3].substring(0, 5));

        let lx = x;
        let ly = y;

        if (line[3][5] == "2") {
            x -= dist;
        } else if (line[3][5] == "0") {
            x += dist;
        } else if (line[3][5] == "3") {
            y -= dist;
        } else if (line[3][5] == "1") {
            y += dist;
        }
        m += (ly + y) * (lx - x) + Math.abs(x - lx) + Math.abs(y - ly);
    }

    return m / 2 + 1;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
