import { getInput } from "../util.ts";

const input = getInput();

/**
 * @returns {Map<string, Set<string>>}
 */
function makeGraph() {
    const map = new Map();
    function add(a, b) {
        let arr = map.get(a);
        if (!arr) {
            arr = new Set();
            map.set(a, arr);
        }
        arr.add(b);
    }
    for (const line of input) {
        const [a, b] = line.split("-");
        add(a, b);
        add(b, a);
    }
    return map;
}

export function part1() {
    const map = makeGraph();

    const groups = new Set();

    for (const [a, val] of map) {
        if (a[0] != "t") continue;

        for (const b of val) {
            for (const c of map.get(b)) {
                if (val.has(c)) {
                    groups.add([a, b, c].toSorted().join(","));
                }
            }
        }
    }

    return groups.size;
}

export function part2() {
    const map = makeGraph();

    const checked = new Set();
    const set = new Set();
    let best = new Set();

    function findGroup(a) {
        if (checked.has(a)) return;

        let valid = true;
        const sub = map.get(a);
        for (const el of set) {
            if (!sub.has(el)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            set.add(a);
            if (set.size > best.size) {
                best = new Set(set);
            }

            for (const el of map.get(a)) {
                if (!set.has(el)) {
                    findGroup(el);
                }
            }

            set.delete(a);
            checked.add(a);
        }
    }

    for (const [key, val] of map) {
        checked.clear();
        findGroup(key);
    }

    return [...best].toSorted().join(",");
}

import { checkAnswers } from "../test.ts";
checkAnswers();
