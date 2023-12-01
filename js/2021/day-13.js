import { getInput } from "../util.js";

const input = getInput();

const index = input.findIndex(x => x.startsWith("fold along"))
const input1 = input.slice(0, index).map(x => x.split(",").map(x => parseInt(x)));
const input2 = input.slice(index).map(x => { let m = x.match(/fold along (.)=(\d+)/); return [m[1], parseInt(m[2])] });

function makeGrid() {
    let width = 0;
    let height = 0;

    for (const [x, y] of input1) {
        width = Math.max(width, x);
        height = Math.max(height, y);
    }
    width += 1;
    height += 1;

    let grid = new Uint8Array(width * height);
    for (const [x, y] of input1) {
        grid[x + y * width] = 1;
    }

    return [grid, width, height];
}

export function part1() {
    let [grid, width, height] = makeGrid();

    let count = 0;
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < 655; x++) {
            count += (grid[x + y * width] |= grid[(1310 - x) + y * width]);
        }
    }
    return count;
}

export function part2() {
    let [grid, width, height] = makeGrid();
    const w = width;

    function foldX(foldX) {
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < foldX; x++) {
                grid[x + y * w] |= grid[(foldX * 2 - x) + y * w];
            }
        }
        width = foldX;
    }
    function foldY(foldY) {
        for (let y = 0; y < foldY; y++) {
            for (let x = 0; x < width; x++) {
                grid[x + y * w] |= grid[x + (foldY * 2 - y) * w];
            }
        }
        height = foldY;
    }

    for (const [dir, num] of input2) {
        if (dir == "x") foldX(num);
        else foldY(num);
    }

    let str = "";
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (grid[x + y * w]) {
                str += "#";
            } else {
                str += ".";
            }
        }
        str += "\n";
    }
    return str;
}

import { checkAnswers } from "../test.js";
checkAnswers();
