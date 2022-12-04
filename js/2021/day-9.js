import { getInput } from "../util.js";
const input = getInput().map(x => [...x].map(y => parseInt(y)));

export function part1() {
    let sum = 0;
    for (let y = 0; y < 100; y++) {
        for (let x = 0; x < 100; x++) {
            let val = input[y][x];

            let top = y == 0 || input[y - 1][x] > val;
            let bottom = y == 99 || input[y + 1][x] > val;
            let left = x == 0 || input[y][x - 1] > val;
            let right = x == 99 || input[y][x + 1] > val;

            if (top && bottom && left && right) {
                sum += val + 1;
            }
        }
    }
    return sum;
}

export function part2() {
    let a = 0, b = 0, c = 0;
    let visited = new Set();

    function flood(x, y) {
        let stack = [[x, y]];
        visited.clear();

        function add(x, y) {
            let id = x + y * 100;
            if (input[y][x] !== 9 && !visited.has(id)) {
                visited.add(id);
                stack.push([x, y]);
            }
        }

        while (stack.length > 0) {
            let [x, y] = stack.pop();

            if (x < 99) add(x + 1, y);
            if (x > 0) add(x - 1, y);
            if (y < 99) add(x, y + 1);
            if (y > 0) add(x, y - 1);
        }

        let s = visited.size;
        if (s > a) {
            c = b;
            b = a;
            a = s;
        } else if (s > b) {
            c = b;
            b = s;
        } else if (s > c) {
            c = s;
        }
    }

    for (let y = 0; y < 100; y++) {
        for (let x = 0; x < 100; x++) {
            let val = input[y][x];

            let top    = y == 0  || input[y - 1][x] > val;
            let bottom = y == 99 || input[y + 1][x] > val;
            let left   = x == 0  || input[y][x - 1] > val;
            let right  = x == 99 || input[y][x + 1] > val;

            if (top && bottom && left && right) {
                flood(x, y);
            }
        }
    }

    return a * b * c;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1()==532);
    console.assert(part2()==1110780);
}
