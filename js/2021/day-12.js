import { getInput } from "../util.js";
const input = getInput().map(x => x.split("-"));

function isUpperCase(str) {
    return str === str.toUpperCase();
}

function buildGraph() {
    let idMap = new Map([["start", 0], ["end", 1]]);
    let graph = [];

    function getId(n) {
        let id = idMap.get(n);
        if (id === undefined) {
            if (isUpperCase(n)) {
                id = idMap.size + 16;
            } else {
                id = idMap.size;
            }
            idMap.set(n, id);
        }
        return id;
    }
    function get(id) {
        let el = graph[id];
        if (!el) {
            el = [];
            graph[id] = el;
        }
        return el;
    }

    for (const [a, b] of input) {
        let aId = getId(a);
        let bId = getId(b);

        if (bId != 0) get(aId).push(bId);
        if (aId != 0) get(bId).push(aId);
    }

    return graph;
}

export function part1() {
    let graph = buildGraph();

    let count = 0;
    function scan(current, visited) {
        visited[current] = true;

        for (const item of graph[current]) {
            if (item === 0) { // start
            } else if (item === 1) { // end
                count++;
            } else if (item > 16 || !visited[item]) {
                scan(item, visited);
            }
        }

        visited[current] = false;
    }

    scan(0, new Array(100).fill(0));
    return count;
}

export function part2() {
    let graph = buildGraph();
    let visited = new Uint8Array(64);

    // let stackPos = 0;
    // let stack = new Uint8Array(128);

    let count = 0;
    function scan(current, special) {
        visited[current] = true;

        for (const item of graph[current]) {
            if (item === 0) { // start
            } else if (item === 1) { // end
                count++;
            } else if (item > 16 || !visited[item]) {
                scan(item, special);
            } else if (!special) {
                scan(item, true);
                visited[item] = true;
            }
        }

        visited[current] = false;
    }

    scan(0, false);
    return count;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 3495);
    console.assert(part2() == 94849);
}
