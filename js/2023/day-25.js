import { getInput } from "../util.js";

const input = getInput();

function shuffle(array) {
    let currentIndex = array.length, randomIndex;

    // While there remain elements to shuffle.
    while (currentIndex > 0) {

        // Pick a remaining element.
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex--;

        // And swap it with the current element.
        [array[currentIndex], array[randomIndex]] = [
            array[randomIndex], array[currentIndex]];
    }

    return array;
}

export function part1() {
    let nodes = new Set();
    let edges = []; // no duplicates exist

    for (let i = 0; i < input.length; i++) {
        let [a, b] = input[i].split(": ");
        b = b.split(" ");

        nodes.add(a);
        for (const el of b) {
            nodes.add(el);
            edges.push([a, el]);
        }
    }

    let dsu = new Map();
    let roots = new Set();

    function reset() {
        roots.clear();
        for (const n of nodes) {
            let g = { parent: null, size: 1 };
            g.parent = g;
            dsu.set(n, g);
            roots.add(g);
        }
    }
    function find(name) {
        let x = dsu.get(name);
        while (x.parent != x) {
            let t = x.parent;
            x.parent = x.parent.parent;
            x = t;
        }
        return x;
    }
    function union(x, y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return;
        }

        if (x.size < y.size) {
            [x, y] = [y, x];
        }

        y.parent = x;
        x.size += y.size;
        roots.delete(y);
    }

    while (true) {
        reset();
        let _edges = [...edges];
        shuffle(_edges);

        while (roots.size > 2) {
            let e = _edges.pop();

            union(e[0], e[1]);
        }

        let count = 0;
        for (let i = 0; i < _edges.length; i++) {
            const e = _edges[i];

            if (find(e[0]) != find(e[1])) {
                count++;
                if (count > 3) break;
            }
        }

        if (count == 3) {
            let r = [...roots];
            return r[0].size * r[1].size;
        }
    }
}

export function part2() {
    return 0;
}

import { checkAnswers } from "../test.js";
checkAnswers();
