import { array_split, getInput } from "../util.js";
const input = array_split(getInput(false), x => x == "");

export function part1() {
    let count = 0;

    for (const group of input) {
        let set = new Set();
        for (const x of group) {
            for (let i = 0; i < x.length; i++) {
                set.add(x.charCodeAt(i))
            }
        }
        count += set.size;
    }

    return count;
}

export function part2() {
    let count = 0;

    for (const group of input) {
        let m = new Map();

        for (const member of group) {
            for (let i = 0; i < member.length; i++) {
                let l = member.charCodeAt(i);
                m.set(l, (m.get(l) ?? 0) + 1);
            }
        }

        for (const [k, val] of m) {
            count += val == group.length;
        }
    }

    return count;

}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 6351);
    console.assert(part2() == 3143);
}
