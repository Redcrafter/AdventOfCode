import { getInput } from "../util.ts";

const input = getInput().map(x => [...x]);

const height = input.length;
const width = input[0].length;

function north(grid) {
    for (let x = 0; x < width; x++) {
        let cached = 0;

        for (let y = height - 1; y >= 0; y--) {
            let c = grid[y][x];
            if (c == "O") {
                cached++;
                grid[y][x] = ".";
            } else if (c == "#") {
                for (let i = 0; i < cached; i++) {
                    grid[y + i + 1][x] = "O";
                }
                cached = 0;
            }
        }
        for (let i = 0; i < cached; i++) {
            grid[i][x] = "O";
        }
    }
}

function south(grid) {
    for (let x = 0; x < width; x++) {
        let cached = 0;

        for (let y = 0; y < height; y++) {
            let c = grid[y][x];
            if (c == "O") {
                cached++;
                grid[y][x] = ".";
            } else if (c == "#") {
                for (let i = 0; i < cached; i++) {
                    grid[y - i - 1][x] = "O";
                }
                cached = 0;
            }
        }
        for (let i = 0; i < cached; i++) {
            grid[height - i - 1][x] = "O";
        }
    }
}

function west(grid) {
    for (let y = 0; y < height; y++) {
        let cached = 0;

        for (let x = width - 1; x >= 0; x--) {
            let c = grid[y][x];
            if (c == "O") {
                cached++;
                grid[y][x] = ".";
            } else if (c == "#") {
                for (let i = 0; i < cached; i++) {
                    grid[y][x + i + 1] = "O";
                }
                cached = 0;
            }
        }
        for (let i = 0; i < cached; i++) {
            grid[y][i] = "O";
        }
    }
}
function east(grid) {
    for (let y = 0; y < height; y++) {
        let cached = 0;

        for (let x = 0; x < width; x++) {
            let c = grid[y][x];
            if (c == "O") {
                cached++;
                grid[y][x] = ".";
            } else if (c == "#") {
                for (let i = 0; i < cached; i++) {
                    grid[y][x - i - 1] = "O";
                }
                cached = 0;
            }
        }
        for (let i = 0; i < cached; i++) {
            grid[y][width - i - 1] = "O";
        }
    }
}

function roll(grid, dx, dy) {
    let moved = true;
    while (moved) {
        moved = false;
        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                if (grid[y][x] == "O" && grid[y + dy]?.[x + dx] == ".") {
                    grid[y + dy][x + dx] = "O";
                    grid[y][x] = ".";
                    moved = true;
                }
            }
        }
    }
}

function weight(grid) {
    let result = 0;
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (grid[y][x] == "O") {
                result += height - y;
            }
        }
    }
    return result;
}

export function part1() {
    let grid = structuredClone(input);
    north(grid);
    return weight(grid);
}

export function part2() {
    let grid = structuredClone(input);

    let map = new Map();

    for (let i = 0; i < 1000000000; i++) {
        north(grid);
        west(grid);
        south(grid);
        east(grid);

        let c = grid.flatMap(x => x.join("")).join("");
        if (map.has(c)) {
            i = 1000000000 - (1000000000 - i) % (i - map.get(c));
        }
        map.set(c, i);
    }

    return weight(grid);
}

import { checkAnswers } from "../test.ts";
checkAnswers();
