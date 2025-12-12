import { getInput } from "../util.ts";

const input = getInput();

const width = input[0].length;
const height = input.length;

function cast(x, y, dx, dy) {
    let visited = new Map();

    function cast(x, y, dx, dy) {
        let dir = 1 << (dx + (dy << 1) + 2);

        while (x >= 0 && x < width && y >= 0 && y < height) {
            let id = x + y * width;
            let t = visited.get(id) ?? 0;
            if ((t & dir) != 0)
                return;

            visited.set(id, t | dir);

            let c = input[y][x];
            if (c == "|" && dx != 0) {
                cast(x, y - 1, 0, -1);
                cast(x, y + 1, 0, 1);
                break;
            } else if (c == "-" && dy != 0) {
                cast(x - 1, y, -1, 0);
                cast(x + 1, y, 1, 0);
                break;
            } else if (c == "/") {
                [dx, dy] = [-dy, -dx];
                dir = 1 << (dx + (dy << 1) + 2);
            } else if (c == "\\") {
                [dx, dy] = [dy, dx];
                dir = 1 << (dx + (dy << 1) + 2);
            }
            x += dx;
            y += dy;
        }
    }
    cast(x, y, dx, dy);
    return visited.size;
}

export function part1() {
    return cast(0, 0, 1, 0);
}

export function part2() {
    let result = 0;
    for (let x = 0; x < width; x++) {
        result = Math.max(result, cast(x, 0, 0, 1));
        result = Math.max(result, cast(x, height - 1, 0, - 1));
    }
    for (let y = 0; y < height; y++) {
        result = Math.max(result, cast(0, y, 1, 0));
        result = Math.max(result, cast(width - 1, y, -1, 0));
    }
    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
