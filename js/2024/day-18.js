import { extractNumbers, getInput } from "../util.ts";

const input = extractNumbers(getInput());
const width = 71;
const height = 71;

function sim(visited) {
    let stack = [];
    let next = [];

    stack.push([0, 0]);

    function add(x, y) {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return

        if (!visited[x + y * width]) {
            visited[x + y * width] = 1;
            next.push([x, y]);
        }
    }

    for (let i = 0; ; i++) {
        while (stack.length != 0) {
            const [x, y] = stack.pop();
            if (x == 70 && y == 70) return i;

            add(x - 1, y);
            add(x + 1, y);
            add(x, y - 1);
            add(x, y + 1);
        }
        if (next.length == 0)
            break;

        [stack, next] = [next, stack];
    }

    return -1;
}

export function part1() {
    const visited = new Uint8Array(width * height);

    for (let i = 0; i < 1024; i++) {
        let [x, y] = input[i];
        visited[x + y * width] = 1;
    }

    return sim(visited);
}

export function part2() {
    const visited = new Uint8Array(width * height);

    let l = 1024;
    let r = input.length - 1;

    while (l < r) {
        const m = Math.floor((l + r) / 2);

        visited.fill(0);
        for (let i = 0; i < m; i++) {
            let [x, y] = input[i];
            visited[x + y * width] = 1;
        }

        if (sim(visited) != -1) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return input[l].join(",");
}

import { checkAnswers } from "../test.ts";
checkAnswers();
