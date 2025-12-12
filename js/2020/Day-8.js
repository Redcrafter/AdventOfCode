import { getInput } from "../util.ts";

const input = getInput().map(x => x.split(" "));

export function part1() {
    let seen = new Uint8Array(input.length);

    let pc = 0;
    let acc = 0;

    while (true) {
        if (seen[pc])
            return acc;
        seen[pc] = 1;

        let [a, b] = input[pc];

        if (a == "jmp") {
            pc += parseInt(b);
        } else if (a == "acc") {
            acc += parseInt(b);
            pc++;
        } else {
            pc++;
        }
    }
}

export function part2() {
    let jumps = input.filter(x => x[0] == "jmp");

    function run() {
        let seen = new Uint8Array(input.length);

        let pc = 0;
        let acc = 0;

        while (pc < input.length) {
            if (seen[pc]) return 0;
            seen[pc] = 1;

            let [a, b] = input[pc];

            if (a == "jmp") {
                pc += parseInt(b);
            } else if (a == "acc") {
                acc += parseInt(b);
                pc++;
            } else {
                pc++;
            }
        }

        return acc;
    }

    for (const item of jumps) {
        item[0] = "nop";

        let res = run();
        if (res != 0) return res;
        item[0] = "jmp";
    }
}

import { checkAnswers } from "../test.ts";
checkAnswers();
