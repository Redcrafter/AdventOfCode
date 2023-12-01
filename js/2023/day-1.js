import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        let val = 0;
        for (let j = 0; j < line.length; j++) {
            const c = line.charCodeAt(j);
            if (c >= 48 && c <= 57) {
                val = (c - 48) * 10;
                break;
            }
        }
        for (let j = line.length - 1; j >= 0; j--) {
            const c = line.charCodeAt(j);
            if (c >= 48 && c <= 57) {
                val += c - 48;
                break;
            }
        }

        result += val;
    }

    return result;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        let val = 0;
        for (let j = 0; j < line.length; j++) {
            const c = line.charCodeAt(j);

            if (c >= 48 && c <= 57) { val = (c - 48) * 10; break; }
            if (c == 111 && line.startsWith("ne", j + 1)) { val = 10; break; }
            if (c == 116 && line.startsWith("wo", j + 1)) { val = 20; break; }
            if (c == 116 && line.startsWith("hree", j + 1)) { val = 30; break; }
            if (c == 102 && line.startsWith("our", j + 1)) { val = 40; break; }
            if (c == 102 && line.startsWith("ive", j + 1)) { val = 50; break; }
            if (c == 115 && line.startsWith("ix", j + 1)) { val = 60; break; }
            if (c == 115 && line.startsWith("even", j + 1)) { val = 70; break; }
            if (c == 101 && line.startsWith("ight", j + 1)) { val = 80; break; }
            if (c == 110 && line.startsWith("ine", j + 1)) { val = 90; break; }
        }

        for (let j = line.length - 1; j >= 0; j--) {
            const c = line.charCodeAt(j);

            if (c >= 48 && c <= 57) { val += c - 48; break; }
            if (c == 111 && line.startsWith("ne", j + 1)) { val += 1; break; }
            if (c == 116 && line.startsWith("wo", j + 1)) { val += 2; break; }
            if (c == 116 && line.startsWith("hree", j + 1)) { val += 3; break; }
            if (c == 102 && line.startsWith("our", j + 1)) { val += 4; break; }
            if (c == 102 && line.startsWith("ive", j + 1)) { val += 5; break; }
            if (c == 115 && line.startsWith("ix", j + 1)) { val += 6; break; }
            if (c == 115 && line.startsWith("even", j + 1)) { val += 7; break; }
            if (c == 101 && line.startsWith("ight", j + 1)) { val += 8; break; }
            if (c == 110 && line.startsWith("ine", j + 1)) { val += 9; break; }
        }

        result += val;
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
