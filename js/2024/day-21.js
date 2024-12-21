import { getInput, zip } from "../util.js";

const input = getInput();
const posi = new Map([
    ["7", [0, 0]], ["8", [1, 0]], ["9", [2, 0]],
    ["4", [0, 1]], ["5", [1, 1]], ["6", [2, 1]],
    ["1", [0, 2]], ["2", [1, 2]], ["3", [2, 2]],
                   ["0", [1, 3]], ["A", [2, 3]],
]);
const arr_pads = new Map([
                   ["^", [1, 0]], ["A", [2, 0]],
    ["<", [0, 1]], ["v", [1, 1]], [">", [2, 1]],
]);

function solve(n_layers) {
    n_layers++;
    const cache = new Map();

    function shortest(start, end, layers) {
        if (layers == 0 || start == end) return 1;

        const str = `${start}${end}${layers}`;
        if (cache.has(str)) return cache.get(str);

        if (!Array.isArray(start))
            start = arr_pads.get(start);
        if (!Array.isArray(end))
            end = arr_pads.get(end);

        let vert, hori;
        if (end[1] < start[1]) vert = "^"
        else if (end[1] > start[1]) vert = "v"

        if (end[0] < start[0]) hori = "<"
        else if (end[0] > start[0]) hori = ">"

        let retVal = 0;

        const dx = Math.abs(end[0] - start[0]) - 1;
        const dy = Math.abs(end[1] - start[1]) - 1;

        if (start[0] == end[0])
            retVal = dy + shortest("A", vert, layers - 1) + shortest(vert, "A", layers - 1);
        else if (start[1] == end[1])
            retVal = dx + shortest("A", hori, layers - 1) + shortest(hori, "A", layers - 1);
        else if (start[0] == 0 && (layers < n_layers || end[1] == 3))
            retVal = dx + dy + shortest("A", hori, layers - 1) + shortest(hori, vert, layers - 1) + shortest(vert, "A", layers - 1);
        else if (end[0] == 0 && (layers < n_layers || start[1] == 3))
            retVal = dx + dy + shortest("A", vert, layers - 1) + shortest(vert, hori, layers - 1) + shortest(hori, "A", layers - 1);
        else
            retVal = dx + dy + Math.min(
                shortest("A", hori, layers - 1) + shortest(hori, vert, layers - 1) + shortest(vert, "A", layers - 1),
                shortest("A", vert, layers - 1) + shortest(vert, hori, layers - 1) + shortest(hori, "A", layers - 1)
            );
        cache.set(str, retVal);
        return retVal;
    }

    let result = 0;
    for (const line of input) {
        let total = 0;
        for (const [startp, endp] of zip("A" + line.slice(0, 3), line)) {
            total += shortest(posi.get(startp), posi.get(endp), n_layers);
        }
        result += parseInt(line) * total;
    }
    return result;
}

export function part1() {
    return solve(2);
}

export function part2() {
    return solve(25);
}

import { checkAnswers } from "../test.js";
checkAnswers();
