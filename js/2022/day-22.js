import { getInput } from "../util.ts";

const input = getInput();

let grid = input.slice(0, 200).map(x => [...x]);
let inst = [...input[200].match(/(\d+)|(L|R)/gm)].map(x => (x == "L" || x == "R") ? x : parseInt(x));

export function part1() {
    let dx = 1;
    let dy = 0;

    let x = grid[0].findIndex(x => x != " ");
    let y = 0;

    for (let i = 0; i < inst.length; i++) {
        let item = inst[i];

        if (item == "L") {
            [dx, dy] = [dy, -dx];
            continue;
        }
        if (item == "R") {
            [dx, dy] = [-dy, dx];
            continue;
        }

        for (let i = 0; i < item; i++) {
            let nextY = (((y + dy) % grid.length) + grid.length) % grid.length;

            if (dy != 0) {
                while (grid[nextY][x] === " " || grid[nextY][x] === undefined) {
                    nextY = (((nextY + dy * 50) % grid.length) + grid.length) % grid.length;
                }
            }
            let row = grid[nextY];

            let nextX = (((x + dx) % row.length) + row.length) % row.length;

            if (dx != 0) {
                while (row[nextX] === " " || row[nextX] === undefined) {
                    nextX = (((nextX + dx * 50) % row.length) + row.length) % row.length;
                }
            }

            if (row[nextX] === "#") {
                break;
            } else if (row[nextX] == ".") {
                x = nextX;
                y = nextY;
            } else {
                debugger
            }
        }
    }

    let res = 0;
    if (dx == 1) res = 0;
    if (dy == 1) res = 1;
    if (dx == -1) res = 2;
    if (dy == -1) res = 3;

    return (y + 1) * 1000 + (x + 1) * 4 + res;
}

export function part2() {
    let top = [];
    let right = [];
    let front = [];
    let bottom = [];
    let left = [];
    let back = [];

    for (let i = 0; i < 50; i++) {
        top.push(grid[i].slice(50, 100));
        right.push(grid[i].slice(100, 150));
        front.push(grid[i + 50].slice(50, 100));

        left.push(grid[i + 100].slice(0, 50));
        bottom.push(grid[i + 100].slice(50, 100));
        back.push(grid[i + 150].slice(0, 50));
    }

    let faces = [
        top,
        right,
        front,
        bottom,
        left,
        back
    ]

    function toGlobal() {
        switch (f) {
            case 0: return [x + 50, y];
            case 1: return [x + 100, y];
            case 2: return [x + 50, y + 50];
            case 3: return [x + 50, y + 100];
            case 4: return [x, y + 100];
            case 5: return [x, y + 150]
        }
    }

    let x = 0;
    let y = 0;
    let f = 0;

    let dx = 1;
    let dy = 0;

    for (let i = 0; i < inst.length; i++) {
        let item = inst[i];

        if (item == "L") {
            [dx, dy] = [dy, -dx];
            continue;
        }
        if (item == "R") {
            [dx, dy] = [-dy, dx];
            continue;
        }

        // console.log(toGlobal());

        for (let j = 0; j < item; j++) {
            let nextX = x + dx;
            let nextY = y + dy;
            let nextDx = dx;
            let nextDy = dy;
            let nextF = f;

            if (nextX < 0) {
                if (f == 0) {
                    nextF = 4;
                    nextX = 0;
                    nextY = 49 - y;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 1) {
                    nextF = 0;
                    nextX = 49;
                    nextY = y;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 2) {
                    nextF = 4;
                    nextX = y;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else if (f == 3) {
                    nextF = 4;
                    nextX = 49;
                    nextY = y;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 4) {
                    nextF = 0;
                    nextX = 0;
                    nextY = 49 - y;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 5) {
                    nextF = 0;
                    nextX = y;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else {
                    debugger
                }
            }
            if (nextX >= 50) {
                if (f == 0) {
                    nextF = 1;
                    nextX = 0;
                    nextY = y;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 1) {
                    nextF = 3;
                    nextX = 49;
                    nextY = 49 - y;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 2) {
                    nextF = 1;
                    nextX = y;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else if (f == 3) {
                    nextF = 1;
                    nextX = 49;
                    nextY = 49 - y;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 4) {
                    nextF = 3;
                    nextX = 0;
                    nextY = y;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 5) {
                    nextF = 3
                    nextX = y;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else {
                    debugger
                }
            }
            if (nextY < 0) {
                if (f == 0) {
                    nextF = 5;
                    nextX = 0;
                    nextY = x;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 1) {
                    nextF = 5;
                    nextX = x;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else if (f == 2) {
                    nextF = 0;
                    nextX = x;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else if (f == 3) {
                    nextF = 2;
                    nextX = x;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else if (f == 4) {
                    nextF = 2;
                    nextX = 0;
                    nextY = x;
                    nextDx = 1;
                    nextDy = 0;
                } else if (f == 5) {
                    nextF = 4;
                    nextX = x;
                    nextY = 49;
                    nextDx = 0;
                    nextDy = -1;
                } else {
                    debugger
                }
            }
            if (nextY >= 50) {
                if (f == 0) {
                    nextF = 2;
                    nextX = x;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else if (f == 1) {
                    nextF = 2;
                    nextX = 49;
                    nextY = x;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 2) {
                    nextF = 3;
                    nextX = x;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else if (f == 3) {
                    nextF = 5;
                    nextX = 49;
                    nextY = x;
                    nextDx = -1;
                    nextDy = 0;
                } else if (f == 4) {
                    nextF = 5;
                    nextX = x;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else if (f == 5) {
                    nextF = 1;
                    nextX = x;
                    nextY = 0;
                    nextDx = 0;
                    nextDy = 1;
                } else {
                    debugger
                }
            }

            let el = faces[nextF][nextY][nextX];

            if (el === "#") {
                break;
            } else if (el == ".") {
                x = nextX;
                y = nextY;
                f = nextF;
                dx = nextDx;
                dy = nextDy;
            } else {
                debugger
            }
        }
    }

    let res = 0;
    if (dx == 1) res = 0;
    if (dy == 1) res = 1;
    if (dx == -1) res = 2;
    if (dy == -1) res = 3;

    let g = toGlobal();
    return (g[1] + 1) * 1000 + (g[0] + 1) * 4 + res;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
