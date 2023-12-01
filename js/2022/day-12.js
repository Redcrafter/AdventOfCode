import { getInput } from "../util.js";

const input = getInput().map(x => [...x].map(y => y.charCodeAt(0)));

const a = 'a'.charCodeAt(0);
const E = 'E'.charCodeAt(0);

function findEnd() {
    for (let y = 0; y < input.length; y++) {
        const line = input[y];
        for (let x = 0; x < line.length; x++) {
            if (line[x] == E) {
                return { x, y };
            }
        }
    }
}

export function part1() {
    const end = findEnd();
    let min = 0;

    const width = input[0].length;
    const height = input.length;

    const graph = new Uint16Array(width * height);
    graph.fill(65535);
    graph[end.x + end.y * width] = 0;

    let pos = 0;

    const heap = [];
    heap.push(end);

    while (pos < heap.length) {
        let currentNode = heap[pos++];

        let x = currentNode.x;
        let y = currentNode.y;

        let to = input[y][x] - a;
        let score = graph[x + y * width];

        if (to == -28) to = 25;
        if (to == -14) to = 0;

        function func(x, y) {
            let from = input[y][x] - a;

            if (from == -28) from = 25;
            if (from == -14) {
                min = score + 1;
            }

            if (to > from + 1)
                return;
            let newScore = score + 1;
            let n = graph[x + y * width];

            if (newScore >= n)
                return;

            graph[x + y * width] = newScore;
            heap.push({ x, y });
        }

        if (x > 0) func(x - 1, y);
        if (x + 1 < width) func(x + 1, y);
        if (y > 0) func(x, y - 1);
        if (y + 1 < height) func(x, y + 1);

        if (min != 0) return min;
    }

    return min;
}

export function part2() {
    const end = findEnd();
    let min = 0;

    const width = input[0].length;
    const height = input.length;

    const graph = new Uint16Array(width * height);
    graph.fill(65535);
    graph[end.x + end.y * width] = 0;

    let pos = 0;

    const heap = [];
    heap.push(end);

    while (pos < heap.length) {
        let currentNode = heap[pos++];

        let x = currentNode.x;
        let y = currentNode.y;

        let to = input[y][x] - a;
        let score = graph[x + y * width];

        if (to == -28) to = 25;
        if (to == -14) to = 0;

        function func(x, y) {
            let from = input[y][x] - a;

            if (from == -28) from = 25;
            if (from == -14) from = 0;

            if (to > from + 1)
                return;
            let newScore = score + 1;
            let n = graph[x + y * width];

            if (newScore >= n)
                return;

            if (from == 0) {
                min = newScore;
                return;
            }

            graph[x + y * width] = newScore;
            heap.push({ x, y });
        }

        if (x > 0) func(x - 1, y);
        if (x + 1 < width) func(x + 1, y);
        if (y > 0) func(x, y - 1);
        if (y + 1 < height) func(x, y + 1);

        if (min != 0) return min;
    }

    return min;
}

import { checkAnswers } from "../test.js";
checkAnswers();
