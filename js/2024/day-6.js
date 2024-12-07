import { getInput } from "../util.js";

const input_ = getInput();
const input = new Uint8Array([...getInput().join("")].map(x => x.charCodeAt(0)));;

const width = input_[0].length;
const height = input_.length;

function findStart() {
    for (let i = 0; i < input.length; i++) {
        if (input[i] == 94) {
            return [i % width, (i / width) | 0];
        }
    }
}

function defaultPath(x, y) {
    const visited = new Uint8Array(width * height);
    visited[x + y * width] = 1;

    let dx = 0;
    let dy = -1;

    while (true) {
        const nx = x + dx;
        const ny = y + dy;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height) return visited;
        if (input[nx + ny * width] == 35) {
            [dx, dy] = [-dy, dx];
        } else {
            x = nx;
            y = ny;
            visited[x + y * width] = 1;
        }
    }
}

export function part1() {
    const start = findStart();
    const visited = defaultPath(start[0], start[1]);
    let result = 0;
    for (let i = 0; i < visited.length; i++) {
        result += visited[i];
    }
    return result;
}

function findLoop(visited, x_, y_) {
    visited.fill(0);

    let x = x_ | 0;
    let y = y_ | 0;
    let dx = 0;
    let dy = -1;

    while (true) {
        const nx = x + dx;
        const ny = y + dy;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height) return 0;

        if (input[nx + ny * width] == 35) {
            if (visited[x + y * width]) return 1;
            visited[x + y * width] = 1;

            [dx, dy] = [-dy, dx];
            while (input[(x + dx) + (y + dy) * width] == 35) {
                [dx, dy] = [-dy, dx];
            }
        } else {
            x = nx;
            y = ny;
        }
    }
}

export function part2() {
    const start = findStart();
    const visited = defaultPath(start[0], start[1]);
    const visited1 = new Uint8Array(width * height);

    visited[start[0] + start[1] * width] = 0;

    let result = 0;
    for (let i = 0; i < visited.length; i++) {
        if (visited[i]) {
            const x = i % width;
            const y = (i / width) | 0;

            input[x + y * width] = 35;
            result += findLoop(visited1, start[0], start[1]);
            input[x + y * width] = 46;
        }
    }
    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
