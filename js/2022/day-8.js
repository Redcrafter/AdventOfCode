import { getInput } from "../util.js";
const input = getInput().flatMap(x => [...x].map(x => +x));

const size = 99;

export function part1() {
    let visited = new Uint8Array(99 * 99);
    let res = 0;

    function ray(x, y, dx, dy) {
        let height = -1;

        while (height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            let v = input[x + y * size];
            if (v > height) {
                height = v;

                if (visited[x + y * size] == 0) res++;
                visited[x + y * size] = 1;
            }

            x += dx;
            y += dy;
        }
    }

    for (let i = 0; i < size; i++) {
        ray(0, i, 1, 0);
        ray(98, i, -1, 0);

        ray(i, 0, 0, 1);
        ray(i, 98, 0, -1);
    }

    return res;
}

export function part2() {
    let best = 0;
    let visited = new Uint8Array(99 * 99);

    function score(x, y, dx, dy) {
        let height = input[x + y * size];

        let score = 0;

        x += dx;
        y += dy;

        while (x < size && y < size & x >= 0 && y >= 0) {
            let v = input[x + y * size];
            score++;
            if (v >= height) {
                break;
            }
            x += dx;
            y += dy;
        }

        return score;
    }

    function ray(x, y, dx, dy) {
        let height = -1;

        while (height < 9 && x < size && y < size & x >= 0 && y >= 0) {
            let v = input[x + y * size];
            if (v > height) {
                height = v;

                if (visited[x + y * size] == 0) {
                    let s = score(x, y, 1, 0) * score(x, y, -1, 0) * score(x, y, 0, 1) * score(x, y, 0, -1);
                    if (s > best) best = s;
                };
                visited[x + y * size] = 1;
            }

            x += dx;
            y += dy;
        }
    }

    for (let i = 0; i < size; i++) {
        ray(0, i, 1, 0);
        ray(98, i, -1, 0);

        ray(i, 0, 0, 1);
        ray(i, 98, 0, -1);
    }

    return best;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.log(part1() == 1859);
    console.log(part2() == 332640);
}
