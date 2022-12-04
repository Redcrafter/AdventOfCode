import { getInput } from "../util.js";
const input = getInput().map(x => x.split(/,| -> /).map(y => parseInt(y)))

export function part1() {
    let grid = new Uint8Array(1000 * 1000);
    let sum = 0;

    for (const [x0, y0, x1, y1] of input) {
        if (x0 == x1) {
            let a = Math.min(y0, y1);
            let b = Math.max(y0, y1);

            for (let y = a; y <= b; y++) {
                sum += grid[y + x0 * 1000] == 1;
                grid[y + x0 * 1000]++;
            }
        } else if (y0 == y1) {
            let a = Math.min(x0, x1);
            let b = Math.max(x0, x1);

            for (let x = a; x <= b; x++) {
                sum += grid[y0 + x * 1000] == 1;
                grid[y0 + x * 1000]++;
            }
        }
    }

    return sum;
}

export function part2() {
    let grid = new Uint8Array(1000 * 1000);
    let sum = 0;

    for (const [x0, y0, x1, y1] of input) {
        let dx = Math.sign(x1 - x0);
        let dy = Math.sign(y1 - y0);

        let x = x0;
        let y = y0;

        while (x != x1 || y != y1) {
            sum += grid[y + x * 1000] == 1;
            grid[y + x * 1000]++;

            x += dx;
            y += dy;
        }
        sum += grid[y + x * 1000] == 1;
        grid[y + x * 1000]++;
    }

    return sum;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 5576);
    console.assert(part2() == 18144);
}
