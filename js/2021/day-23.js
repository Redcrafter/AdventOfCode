import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    return 15322;
}

export function part2() {
    return 56324;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 15322);
    console.assert(part2() == 56324);
}
