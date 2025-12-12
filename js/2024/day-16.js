import { getInput, sum } from "../util.ts";

const input_ = getInput();
const height = input_.length;
const width = input_[0].length;
const input = new Uint8Array(input_.flatMap(x => [...x].map(x => x.charCodeAt(0))))

function buildGrid() {
    const grid = new Uint32Array(width * height);
    grid.fill(1 << 30);

    const stack = [];
    stack.push([1, height - 2, 1, 0, 0]);

    function tryStep(x, y, dx, dy, score) {
        const x1 = x + dx;
        const y1 = y + dy;

        if (input[x1 + y1 * width] == 35) return;
        if (score < grid[x1 + y1 * width]) {
            grid[x1 + y1 * width] = score;

            stack.push([x1, y1, dx, dy, score]);
        }
    }

    while (stack.length > 0) {
        const [x, y, dx, dy, score] = stack.shift();

        tryStep(x, y, dx, dy, score + 1); // step forward
        tryStep(x, y, -dy, dx, score + 1000 + 1); // turn right
        tryStep(x, y, dy, -dx, score + 1000 + 1); // turn left
    }

    return grid;
}

export function part1() {
    const grid = buildGrid();
    return grid[(width - 2) + 1 * width];
}

export function part2() {
    const grid = buildGrid();

    const visited = new Uint8Array(width * height);

    function trace(x, y, dx, dy, score) {
        let lastX = x;
        let lastY = y;

        x += dx;
        y += dy;
        score--;

        if (grid[x + y * width] != score) return false;
        if (visited[x + y * width]) return true;

        visited[x + y * width] = 1;

        let valid = false;
        while (true) {
            if (input[x + y * width] == 35) break;

            visited[x + y * width] = 1;
            if (x == 1 && y == height - 2) {
                return true;
            }

            if (input[(x - dy) + (y + dx) * width] != 35) {
                if (trace(x, y, -dy, dx, score - 1000)) {
                    valid = true;
                    lastX = x;
                    lastY = y;
                }
            }
            if (input[(x + dy) + (y - dx) * width] != 35) {
                if (trace(x, y, dy, -dx, score - 1000)) {
                    valid = true;
                    lastX = x;
                    lastY = y;
                }
            }

            x += dx;
            y += dy;
            score--;
        }

        x -= dx;
        y -= dy;
        while (x != lastX || y != lastY) { // go back to last valid location and clean up unused spaces
            visited[x + y * width] = 0;
            x -= dx;
            y -= dy;
        }

        return valid;
    }

    visited[width - 2 + width] = 1;
    trace(width - 2, 1, -1, 0, grid[(width - 2) + 1 * width]);
    trace(width - 2, 1, 0, 1, grid[(width - 2) + 1 * width]);

    return sum(visited);
}

import { checkAnswers } from "../test.ts";
checkAnswers();
