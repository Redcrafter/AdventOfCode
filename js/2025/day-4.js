import { getInput } from "../util.ts";

const input = getInput();

export function part1() {
    let res = 0;

    const width = input[0].length;
    for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < width; x++) {
            const char = line[x];
            if (char != "@") continue;

            const tl = input[y - 1]?.[x - 1] == "@";
            const t  = input[y - 1]?.[x + 0] == "@";
            const tr = input[y - 1]?.[x + 1] == "@";

            const l  = input[y + 0]?.[x - 1] == "@";
            const r  = input[y + 0]?.[x + 1] == "@";

            const bl = input[y + 1]?.[x - 1] == "@";
            const b  = input[y + 1]?.[x + 0] == "@";
            const br = input[y + 1]?.[x + 1] == "@";

            if (tl + t + tr + l + r + bl + b + br < 4)
                res++;
        }
    }

    return res;
}

export function part2() {
    let res = 0;

    const removed = new Set();

    const width = input[0].length;
    function test(x, y) {
        return removed.has(x + y * width);
    }

    while (true) {
        let changed = false;

        for (let y = 0; y < input.length; y++) {
            const line = input[y];
    
            for (let x = 0; x < line.length; x++) {
                const char = line[x];
    
                if (char != "@" || test(x, y)) continue;
    
                let tl = input[y - 1]?.[x - 1] == "@" && !test(x - 1, y - 1);
                let t  = input[y - 1]?.[x + 0] == "@" && !test(x + 0, y - 1);
                let tr = input[y - 1]?.[x + 1] == "@" && !test(x + 1, y - 1);
    
                let l  = input[y + 0]?.[x - 1] == "@" && !test(x - 1, y + 0);
                let r  = input[y + 0]?.[x + 1] == "@" && !test(x + 1, y + 0);
    
                let bl = input[y + 1]?.[x - 1] == "@" && !test(x - 1, y + 1);
                let b  = input[y + 1]?.[x + 0] == "@" && !test(x + 0, y + 1);
                let br = input[y + 1]?.[x + 1] == "@" && !test(x + 1, y + 1);
    
                let c = tl + t + tr + l + r + bl + b + br;
                if (c < 4) {
                    changed = true;
                    removed.add(x + y * width);
                    res++;
                }
    
            }
        }

        if(!changed) break;
    }

    return res;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
