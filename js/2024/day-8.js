import { getInput, sum } from "../util.js";

const input = getInput().map(x => [...x].map(x => x.charCodeAt(0)));
const height = input.length;
const width = input[0].length;

function findGroups() {
    const groups = new Array(256);
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            const el = input[y][x];
            if (el == 46) continue;

            let g = groups[el];
            if (!g) {
                g = [];
                groups[el] = g;
            }
            g.push([x, y]);
        }
    }
    return groups;
}

export function part1() {
    const groups = findGroups();

    const set = new Uint8Array(width * height);
    function add(x, y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            set[x + y * width] = 1;
        }
    }

    for (const g of groups) {
        if (!g) continue;
        for (let i = 0; i < g.length; i++) {
            const a = g[i];
            for (let j = i + 1; j < g.length; j++) {
                const b = g[j];

                const dx = a[0] - b[0];
                const dy = a[1] - b[1];

                add(a[0] + dx, a[1] + dy);
                add(b[0] - dx, b[1] - dy);
            }
        }
    }

    return sum(set);
}

export function part2() {
    const groups = findGroups();

    const set = new Uint8Array(width * height);
    function add(x, y) {
        set[x + y * width] = 1;
    }

    for (const g of groups) {
        if (!g) continue;

        for (let i = 0; i < g.length; i++) {
            const a = g[i];
            for (let j = i + 1; j < g.length; j++) {
                const b = g[j];

                const dx = a[0] - b[0];
                const dy = a[1] - b[1];

                for (let i = 0; ; i++) {
                    const x = a[0] + dx * i;
                    const y = a[1] + dy * i;
                    if (x < 0 || x >= width || y < 0 || y >= height) break;
                    add(x, y);
                }

                for (let i = 0; ; i++) {
                    const x = a[0] - dx * i;
                    const y = a[1] - dy * i;
                    if (x < 0 || x >= width || y < 0 || y >= height) break;
                    add(x, y);
                }
            }
        }
    }

    return sum(set);
}

import { checkAnswers } from "../test.js";
checkAnswers();
