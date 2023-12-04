import { getInput, parseInt } from "../util.js";

const input = getInput();

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];
        const s = line.split(/[:;,]? /g);

        let ok = true;
        for (let i = 2; i < s.length; i += 2) {
            const count = parseInt(s[i]);
            const color = s[i + 1].charCodeAt(0);

            if ((color == 114 && count > 12) || (color == 103 && count > 13) || count > 14) {
                ok = false;
                break;
            }
        }

        if (ok) {
            result += parseInt(s[1]);
        }
    }

    return result;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];
        const s = line.split(/[:;,]? /g);

        let r = 0;
        let g = 0;
        let b = 0;
        for (let i = 2; i < s.length; i += 2) {
            const count = parseInt(s[i]);
            const color = s[i + 1].charCodeAt(0);

            if (color === 114) r = count > r ? count : r;
            else if (color === 103) g = count > g ? count : g;
            else b = count > b ? count : b;
        }
        result += r * g * b;
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
