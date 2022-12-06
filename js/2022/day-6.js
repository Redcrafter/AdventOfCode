import { getInput, window } from "../util.js";
const input = [...getInput()[0]].map(x => x.charCodeAt(0) - 'a'.charCodeAt(0));

function s1(size) {
    let set = new Set();
    let start = 0;

    for (let i = 0; i < input.length;) {
        const c = input[i];

        if (set.has(c)) {
            set.clear();
            i = start + 1;
            start++;
        } else {
            set.add(c);
            i++;

            if (set.size == size) {
                return start + size;
            }
        }
    }
}

function s2(size) {
    size--;

    let set = [];
    for (let i = 0; i < input.length; i++) {
        const c = input[i];

        let t = set.indexOf(c);

        if (t == -1) {
            if (set.length == size) return i + 1;
        } else {
            for (let i = 0; i <= t; i++) {
                set.shift();
            }
        }
        set.push(c);
    }
}

function s3(size) {
    return window(input, size).findIndex(x => new Set(x).size == size) + size;
}

function s4(size) {
    size--;
    let counter = new Int32Array(26);
    let invalid = 0;

    function add(c) {
        if (counter[c] == 1) {
            invalid++;
        }
        counter[c]++;
    }
    for (let i = 0; i < size; i++) {
        add(input[i]);
    }

    for (let i = size; i < input.length; i++) {
        let c = input[i];

        if (counter[c] == 1) {
            invalid++;
        }
        counter[c]++;

        if (invalid == 0) return i + 1;

        let b = input[i - size];
        if (counter[b] == 2) {
            invalid--;
        }
        counter[b]--;
    }
}

export function part1() {
    return s4(4);
}

export function part2() {
    return s4(14);
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 1953);
    console.assert(part2() == 2301);
}
