import { getInput } from "../util.ts";

const input = getInput().map(x => [x[0], parseInt(x.substring(1))]);

export function part1() {
    let x = 0;
    let y = 0;

    let dx = 1;
    let dy = 0;

    for (let [dir, dist] of input) {
        switch (dir) {
            case "F":
                x += dx * dist;
                y += dy * dist;
                break;
            case "L":
                while (dist > 0) {
                    [dx, dy] = [-dy, dx];
                    dist -= 90;
                }
                break;
            case "R":
                while (dist > 0) {
                    [dx, dy] = [dy, -dx];
                    dist -= 90;
                }
                break;
            case "N":
                y += dist;
                break;
            case "S":
                y -= dist;
                break;
            case "E":
                x += dist;
                break;
            case "W":
                x -= dist;
                break;
        }
    }

    return Math.abs(x) + Math.abs(y);
}

export function part2() {
    let x = 0;
    let y = 0;

    let wx = 10;
    let wy = 1;

    for (let [dir, dist] of input) {
        switch (dir) {
            case "F":
                x += wx * dist;
                y += wy * dist;
                break;
            case "L":
                while (dist > 0) {
                    [wx, wy] = [-wy, wx];
                    dist -= 90;
                }
                break;
            case "R":
                while (dist > 0) {
                    [wx, wy] = [wy, -wx];
                    dist -= 90;
                }
                break;
            case "N":
                wy += dist;
                break;
            case "S":
                wy -= dist;
                break;
            case "E":
                wx += dist;
                break;
            case "W":
                wx -= dist;
                break;
        }
    }

    return Math.abs(x) + Math.abs(y);
}


import { checkAnswers } from "../test.ts";
checkAnswers();
