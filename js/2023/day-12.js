import { getInput } from "../util.js";

const input = getInput();

function solveLine(nums, line) {
    let cache = new Map();
    function rec(numi, pos) {
        let id = (numi * 128) + pos;
        if (cache.has(id)) return cache.get(id);

        const num = nums[numi];

        if (num + pos > line.length || line[pos + num] == 1) {
            return 0;
        }
        for (let p = pos; p < pos + num; p++) {
            if (line[p] == -1) {
                return 0;
            }
        }

        let n = 0;
        if (numi + 1 < nums.length) {
            for (let i = pos + num + 1; i < line.length; i++) {
                if (i > 0 && line[i - 1] == 1) {
                    break;
                }
                n += rec(numi + 1, i);
            }
        } else {
            for (let i = pos + num + 1; i < line.length; i++) {
                if (line[i] == 1) {
                    return 0;
                }
            }
            n++;
        }
        cache.set(id, n);
        return n;
    }

    let asd = 0;
    for (let i = 0; i < line.length; i++) {
        if (i > 0 && line[i - 1] == 1) {
            break;
        }
        asd += rec(0, i);
    }

    return asd;
}

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split(" ");

        let asd = b.split(",").map(x => parseInt(x));

        let line = [...a].map(x => {
            if (x == ".") return -1;
            else if (x == '#') return 1;
            else return 0;
        });

        let v = solveLine(asd, line, 0, 0);
        result += v;
    }

    return result;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split(" ");
        
        let asd = b.split(",").map(x => parseInt(x));

        let line = [...[a, a, a, a, a].join("?")].map(x => {
            if (x == ".") return -1;
            else if (x == '#') return 1;
            else return 0;
        });

        let c = [...asd, ...asd, ...asd, ...asd, ...asd];

        let v = solveLine(c, line);
        result += v;
    }

    return result
}

import { checkAnswers } from "../test.js";
checkAnswers();
