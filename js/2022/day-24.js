import { getInput } from "../util.js";

const input = getInput().map(x => [...x]);

const height = input.length;
const width = input[0].length;
const w2 = width - 2;
const h2 = height - 2;
const size = width * height;

function loadMap() {
    let map = new Uint8Array(width * height);
    for (let y = 0; y < input.length; y++) {
        const line = input[y];
        for (let x = 0; x < line.length; x++) {
            const item = line[x];

            if (item == "#") {
                map[x + y * width] = 16;
            } else if (item == ">") {
                map[x + y * width] = 1;
            } else if (item == "<") {
                map[x + y * width] = 2;
            } else if (item == "v") {
                map[x + y * width] = 4;
            } else if (item == "^") {
                map[x + y * width] = 8;
            }
        }
    }
    map[1] = 32;
    return map;
}

let oldMap = new Uint8Array(width * height);
function doStep(map) {
    oldMap.fill(0);
    let nMap = oldMap;

    if (map[1]) {
        nMap[1] |= 32;
        nMap[width + 1] |= 32;
    }
    if (map[size - 2]) {
        nMap[size - 2] |= 32;
        nMap[size - 2 - width] |= 32;
    }

    const s1 = height - 1;
    const s2 = width - 1;

    for (let y = 1; y < s1; y++) {
        for (let x = 1; x < s2; x++) {
            const p = x + y * width;
            const item = map[p];

            if (item & 1) {
                nMap[(x % w2) + 1 + y * width] |= 1;
            }
            if (item & 2) {
                nMap[(x - 2 + w2) % w2 + 1 + y * width] |= 2;
            }
            if (item & 4) {
                nMap[x + ((y % h2) + 1) * width] |= 4;
            }
            if (item & 8) {
                nMap[x + ((y - 2 + h2) % h2 + 1) * width] |= 8;
            }

            if (!(item & 31) && (item & 32)) {
                nMap[p] |= 32;
                nMap[p + 1] |= 32;
                nMap[p - 1] |= 32;
                nMap[p + width] |= 32;
                nMap[p - width] |= 32;
            }
        }
    }

    oldMap = map;
    return nMap;
}

export function part1() {
    let map = loadMap();
    const ep = width - 2 + (height - 1) * width;

    let i = 0;
    while (!(map[ep] & 32)) {
        i++;
        map = doStep(map);
    }
    return i;
}

export function part2() {
    let map = loadMap();
    const ep = width - 2 + (height - 1) * width;

    let i = 0;
    while (!(map[ep] & 32)) {
        i++;
        map = doStep(map);
    }

    for (let i = 0; i < size; i++) {
        map[i] &= ~32;
    }
    map[ep] = 32;

    while (!(map[1] & 32)) {
        i++;
        map = doStep(map);
    }

    for (let i = 0; i < size; i++) {
        map[i] &= ~32;
    }
    map[1] = 32;
    while (!(map[ep] & 32)) {
        i++;
        map = doStep(map);
    }

    return i;
}

import { checkAnswers } from "../test.js";
checkAnswers();
