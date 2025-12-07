import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    const height = input.length;
    const width = input[0].length;
    const visited = new Uint8Array(width * height);

    function run(x, y) {
        if(visited[x + y * width]) return 0;
        visited[x + y * width] = 1;

        if (y + 1 == height) return 0;

        if (input[y + 1][x] == "^") {
            return run(x + 1, y + 1) + run(x - 1, y + 1) + 1;
        } else {
            return run(x, y + 1);
        }
    }

    return run(input[0].indexOf("S"), 0);
}

export function part2() {
    const height = input.length;
    const width = input[0].length;
    const visited = new Float64Array(width * height);

    function run(x, y) {
        if (visited[x + y * width]) return visited[x + y * width];

        if (y + 1 == height) return 1;

        let v = 0;
        if (input[y + 1][x] == "^") {
            v = run(x + 1, y + 1) + run(x - 1, y + 1);
        } else {
            v = run(x, y + 1);
        }
        visited[x + y * width] = v;
        return v;
    }

    return run(input[0].indexOf("S"), 0);
}

import { checkAnswers } from "../test.js";
checkAnswers();
