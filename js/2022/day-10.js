import { getInput, parseInt } from "../util.js";
const input = getInput();

export function part1() {
    let res = 0;

    let x = 1;
    let cycles = -20;

    for (let i = 0; i < input.length; i++) {
        const item = input[i];

        if (item[0] == "n") {
            cycles++;
            if (cycles % 40 == 0) {
                res += x * (cycles + 20);
            }
        } else {
            cycles++;
            if (cycles % 40 == 0) {
                res += x * (cycles + 20);
            }
            cycles++;
            if (cycles % 40 == 0) {
                res += x * (cycles + 20);
            }
            x += parseInt(item, 5);
        }
    }

    return res;
}

export function part2() {
    let x = 1;
    let cycles = 0;

    let str = new Array(6 * 41);

    function crtPx() {
        let cx = (cycles % 40);
        let cy = Math.floor(cycles / 40);

        str[cx + cy * 41] = (cx == x - 1 || cx == x || cx == x + 1) ? "X" : " ";
    }

    for (let i = 0; i < input.length; i++) {
        const item = input[i];

        if (item[0] == "n") {
            crtPx();
            cycles++;
        } else {
            crtPx();
            cycles++;
            crtPx();
            cycles++;

            x += parseInt(item, 5);
        }
    }

    str[40] = "\n";
    str[81] = "\n";
    str[122] = "\n";
    str[163] = "\n";
    str[204] = "\n";

    return str.join("");
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 13520);
    console.log(part2());
}
