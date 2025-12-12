import { getInput, extractNumbers } from "../util.ts";

const input = extractNumbers(getInput());

function test(line) {
    if (line[0] <= line[line.length - 1]) {
        for (let i = 1; i < line.length; i++) {
            const a = line[i - 1];
            const b = line[i];
            if (a >= b || (b - a) > 3) return 0;
        }
    } else {
        for (let i = 1; i < line.length; i++) {
            const a = line[i - 1];
            const b = line[i];
            if (a <= b || (a - b) > 3) return 0;
        }
    }
    return 1;
}

export function part1() {
    let result = 0;
    for (let i = 0; i < input.length; i++) {
        result += test(input[i]);
    }
    return result;
}

// no tempaltes in js so i just have to copy the function
function testAscending(line) {
    function t(a, b) {
        return a < b && (b - a) <= 3;
    }
    function cont(i) {
        for (; i < line.length - 1; i++) {
            if (!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    }

    for (let i = 0; i < line.length - 1; i++) {
        const a = line[i];
        const b = line[i + 1];
        if (!t(a, b)) {
            // try skipping the left
            if ((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if (i == line.length - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}

function testDescending(line) {
    function t(a, b) {
        return a > b && (a - b) <= 3;
    }
    function cont(i) {
        for (; i < line.length - 1; i++) {
            if (!t(line[i], line[i + 1])) {
                return false;
            }
        }
        return true;
    }

    for (let i = 0; i < line.length - 1; i++) {
        const a = line[i];
        const b = line[i + 1];
        if (!t(a, b)) {
            // try skipping the left
            if ((i == 0 || t(line[i - 1], line[i + 1])) && cont(i + 1)) {
                return true;
            }
            // try skipping the right
            if (i == line.length - 2 || (t(line[i], line[i + 2])) && cont(i + 2)) {
                return true;
            }
            return false;
        }
    }
    return true;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        if (line[0] > line[line.length - 1] || line[1] > line[line.length - 1] || line[0] > line[line.length - 2]) {
            if (testDescending(line)) {
                result++;
                continue;
            }
        }
        if (line[0] < line[line.length - 1] || line[1] < line[line.length - 1] || line[0] < line[line.length - 2]) {
            if (testAscending(line)) {
                result++;
                continue;
            }
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
