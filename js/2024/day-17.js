import { extractNumbers, getInput } from "../util.ts";

// const input = getInput();
const input = extractNumbers(getInput());

function run(a, program) {
    let b = 0;
    let c = 0;
    let pc = 0;

    function combo(i) {
        switch (i) {
            case 0: return 0;
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return a;
            case 5: return b;
            case 6: return c;
            default: throw new Error("");
        }
    }

    let result = [];
    while (pc < program.length) {
        const op = program[pc];
        const param = program[pc + 1];

        switch (op) {
            case 0: a = Math.floor(a / (2 ** combo(param))); break;
            case 1: b = b ^ param; break;
            case 2: b = combo(param) % 8; break;
            case 3:
                if (a != 0) {
                    pc = param;
                    continue;
                }
                break;
            case 4: b = b ^ c; break;
            case 5: result.push(combo(param) % 8); break;
            case 6: b = Math.floor(a / (2 ** combo(param))); break;
            case 7: c = Math.floor(a / (2 ** combo(param))); break;
        }
        pc += 2;
    }
    return result;
}

export function part1() {
    return run(input[0][0], input[3]).join(",");
}

function run1(a, program) {
    let b = 0n;
    let c = 0n;
    let pc = 0;

    function combo(i) {
        switch (i) {
            case 0: return 0n;
            case 1: return 1n;
            case 2: return 2n;
            case 3: return 3n;
            case 4: return a;
            case 5: return b;
            case 6: return c;
            default: throw new Error("");
        }
    }

    const result = [];
    while (pc < program.length) {
        const op = program[pc];
        const param = program[pc + 1];

        switch (op) {
            case 0: a = (a / (2n ** combo(param))); break;
            case 1: b = b ^ BigInt(param); break;
            case 2: b = combo(param) % 8n; break;
            case 3:
                if (a != 0) {
                    pc = param;
                    continue;
                }
                break;
            case 4: b = b ^ c; break;
            case 5: result.push(combo(param) % 8n); break;
            case 6: b = (a / (2n ** combo(param))); break;
            case 7: c = (a / (2n ** combo(param))); break;
        }
        pc += 2;
    }
    return result;
}

export function part2() {
    const program = input[3];

    function findNext(a) {
        for (let i = 0n; i < 8n; i++) {
            const res = run1(a * 8n + i, program);
            if (res.length == 0) continue;

            if (res[0] == program[program.length - res.length]) {
                if (res.length == program.length) {
                    return a * 8n + i;
                }
                const r = findNext(a * 8n + i);
                if (r != 0) return r;
            }
        }
        return 0;
    }
    return Number(findNext(0n));
}

import { checkAnswers } from "../test.ts";
checkAnswers();
