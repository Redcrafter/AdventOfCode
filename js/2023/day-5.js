import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput());

export function part1() {
    let result = Infinity;

    let seeds = input[0];

    let maps = [];

    let start = 2;
    for (let i = 2; i < input.length; i++) {
        if (input[i] == undefined) {
            maps.push(input.slice(start, i));
            start = i + 1;
        }
    }
    maps.push(input.slice(start));

    for (let i = 0; i < seeds.length; i++) {
        let val = seeds[i];

        for (let j = 0; j < maps.length; j++) {
            const map = maps[j];

            for (let k = 0; k < map.length; k++) {
                const [drs, srs, len] = map[k];

                if (val >= srs && val < srs + len) {
                    val = (val - srs) + drs;
                    break;
                }
            }
        }

        result = Math.min(val, result);
    }

    return result;
}
export function part2() {
    let result = Infinity;

    let seeds = input[0];

    let maps = [];

    let start = 2;
    for (let i = 2; i < input.length; i++) {
        if (input[i] == undefined) {
            maps.push(input.slice(start, i));
            start = i + 1;
        }
    }
    maps.push(input.slice(start));

    for (const map of maps) {
        map.sort((a, b) => a[1] - b[1]);

        let first = map[0];
        map.unshift([0, 0, first[1]]);

        let last = map.at(-1);
        map.push([last[1] + last[2], last[1] + last[2], Infinity])
    }

    let _seeds = [];
    for (let i = 0; i < seeds.length; i += 2) {
        _seeds.push([seeds[i], seeds[i] + seeds[i + 1]]);
    }

    for (let j = 0; j < maps.length; j++) {
        const map = maps[j];
        let nseeds = [];

        for (const [seed1, seed2] of _seeds) {
            for (let k = 0; k < map.length; k++) {
                const [dest1, source1, sourcel] = map[k];

                let int1 = Math.max(seed1, source1);
                let int2 = Math.min(seed2, source1 + sourcel)
                if (int1 < int2)
                    nseeds.push([int1 + dest1 - source1, int2 + dest1 - source1])
            }
        }

        _seeds = nseeds;
    }

    for (const r of _seeds) {
        result = Math.min(result, r[0]);
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
