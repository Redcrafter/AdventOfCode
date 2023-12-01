import { getInput } from "../util.js";

/** @type { [string, number, string[]] } */
const input = getInput().map(x => {
    let m = x.match(/Valve (..) has flow rate=(\d+); tunnels? leads? to valves? (.+)/);
    return [m[1], parseInt(m[2]), m[3].split(", ")]
});

export function part1_old() {
    let m = new Map(input.map(x => [x[0], x]));

    let g = new Map();
    for (const item of input) {
        g.set(item[0], new Map(item[2].map(x => [x, 1])));
    }

    let change = true;
    while (change) {
        change = false;
        for (const [k0, v0] of g) {
            for (const [k1, v1] of v0) {
                for (const [k2, v2] of g.get(k1)) {
                    let asd = v0.get(k2);
                    if (!asd || v1 + v2 < asd) {
                        v0.set(k2, v1 + v2);
                        change = true;
                    }
                }
            }
        }
    }

    for (const [k, v] of g) {
        v.delete(k);

        for (const [k1, v1] of [...v]) {
            if (m.get(k1)[1] == 0) {
                v.delete(k1);
            }
        }
    }

    let visited = new Set();
    function step(time, current) {
        if (time <= 0) return 0;

        if (visited.has(current)) return 0;
        visited.add(current);

        let dat = m.get(current);
        let nei = g.get(current);

        let v = (time - 1) * dat[1];
        let score = 0;

        for (const [a, b] of nei) {
            let s2 = step(time - b - 1, a) + v;
            score = Math.max(score, s2);
        }

        visited.delete(current);
        return score;
    }

    let s = 0;
    for (const [k, v] of g.get("AA")) {
        s = Math.max(s, step(30 - v, k));
    }
    return s;
}

// takes minutes to run
export function part2_old() {
    let m = new Map(input.map(x => [x[0], x]));

    let g = new Map();
    for (const item of input) {
        g.set(item[0], new Map(item[2].map(x => [x, 1])));
    }

    let change = true;
    while (change) {
        change = false;
        for (const [k0, v0] of g) {
            for (const [k1, v1] of v0) {
                for (const [k2, v2] of g.get(k1)) {
                    let asd = v0.get(k2);
                    if (!asd || v1 + v2 < asd) {
                        v0.set(k2, v1 + v2);
                        change = true;
                    }
                }
            }
        }
    }

    for (const [k, v] of g) {
        v.delete(k);

        for (const [k1, v1] of [...v]) {
            if (m.get(k1)[1] == 0) {
                v.delete(k1);
            }
        }
    }

    let visited = new Set();

    function step(time, wait1, current1, wait2, current2) {
        let min = Math.min(wait1, wait2);
        wait1 -= min;
        wait2 -= min;
        time -= min;

        if (time < 0) {
            return 0;
        }

        let score = 0;
        let s1 = m.get(current1)[1] * time;
        let s2 = m.get(current2)[1] * time;

        let nei1 = g.get(current1);
        let nei2 = g.get(current2);

        if (wait1 == 0 && wait2 == 0) {
            if (time < 2) return s1 + s2;

            for (const a of nei1) {
                if (visited.has(a[0])) continue;
                visited.add(a[0]);

                for (const b of nei2) {
                    if (visited.has(b[0])) continue;
                    visited.add(b[0]);

                    let res = step(time, a[1] + 1, a[0], b[1] + 1, b[0]) + s1 + s2;
                    score = Math.max(score, res);

                    visited.delete(b[0]);
                }

                visited.delete(a[0]);
            }
        } else if (wait1 == 0) {
            if (time == 0) return s1;

            let ok = false;

            for (const [k, v] of nei1) {
                if (visited.has(k)) continue;
                visited.add(k);

                ok = true;

                let res = step(time, v + 1, k, wait2, current2) + s1;
                score = Math.max(score, res);

                visited.delete(k);
            }

            if (!ok) {
                if (wait2 !== Infinity) {
                    return step(time, Infinity, current1, wait2, current2) + s1;
                } else {
                    return s1;
                }
            }
        } else if (wait2 == 0) {
            if (time == 0) return s2;

            let ok = false;

            for (const [k, v] of nei2) {
                if (visited.has(k)) continue;
                visited.add(k);

                ok = true;

                let res = step(time, wait1, current1, v + 1, k) + s2;
                score = Math.max(score, res);

                visited.delete(k);
            }

            if (!ok && wait1 !== Infinity) {
                if (wait1 !== Infinity) {
                    return step(time, wait1, current1, Infinity, current2) + s2;
                } else {
                    return s2;
                }
            }
        }

        return score;
    }

    let score = 0;
    let n = [...g.get("AA")];

    for (let i = 0; i < n.length; i++) {
        let a = n[i];
        visited.add(a[0]);

        for (let j = i + 1; j < n.length; j++) {
            let b = n[j];
            visited.add(b[0]);

            let res = step(26, a[1] + 1, a[0], b[1] + 1, b[0]);
            // console.log(a, b, res);

            score = Math.max(score, res);
            visited.delete(b[0]);
        }
        visited.delete(a[0]);
    }
    return score;
}

// improved solutions inspired by https://github.com/Salatmate/AoC2022/blob/main/Day16.py

function calcStuff() {
    let idMap = new Map(input.map((x, i) => [x[0], i]));

    const size = input.length;
    const dist = new Int32Array(size * size);
    dist.fill(99);
    const prio = [];

    for (let i = 0; i < size; i++) {
        const item = input[i];
        dist[i + i * size] = 0;

        if (item[1] != 0) prio.push(item[0]);

        for (const n of item[2]) {
            let j = idMap.get(n);

            dist[i + j * size] = 1;
        }
    }

    // https://en.wikipedia.org/wiki/Floyd-Warshall_algorithm
    for (let k = 0; k < size; k++) {
        for (let i = 0; i < size; i++) {
            for (let j = 0; j < size; j++) {
                if (dist[i + j * size] > dist[i + k * size] + dist[k + j * size])
                    dist[i + j * size] = dist[i + k * size] + dist[k + j * size]
            }
        }
    }

    prio.push("AA");

    // console.assert(prio.length < 32);

    const bitCount = prio.length - 1;
    const prioSet = (2 ** bitCount) - 1;
    const times = new Int32Array(bitCount);

    const bitDist = []; // todo: could replace with array
    for (let i = 0; i < prio.length; i++) {
        const a = prio[i];
        let aId = idMap.get(a);
        let distLine = [];

        for (let j = 0; j < prio.length; j++) {
            const b = prio[j];

            distLine[j] = dist[aId + idMap.get(b) * size];
        }
        bitDist[i] = distLine;

        times[i] = input[aId][1];
    }

    return [bitCount, prioSet, bitDist, times];
}

export function part1() {
    const [bitCount, prioSet, bitDist, times] = calcStuff();

    // "AA" -> last item of prio so bitCount
    const paths = [[30, 0, bitCount, prioSet]];
    let pos = 0;
    let max = 0;

    let maxRate = Math.max(...times);

    while (pos < paths.length) {
        const el = paths[pos++];
        const time = el[0];
        const pressure = el[1];
        const curr = el[2];
        const remaining = el[3];
    
        const dist = bitDist[curr];

        if (pressure + time * maxRate < max) continue;
        max = Math.max(max, pressure);

        for (let i = 0; i < bitCount; i++) {
            let mask = 1 << i;
            if (!(remaining & mask)) continue;

            let newtime = time - dist[i] - 1;
            if (newtime > 0) {
                let newpressure = pressure + newtime * times[i];
                let newremaining = remaining & ~mask;
                paths.push([newtime, newpressure, i, newremaining]);
            }
        }
    }

    return max;
}

export function part2() {
    const [bitCount, prioSet, bitDist, times] = calcStuff();

    // "AA" -> last item of prio so bitCount
    const paths = [[26, 0, bitCount, prioSet]];
    const best = new Uint16Array(prioSet);

    while (paths.length) {
        const el = paths.pop();
        const time = el[0];
        const pressure = el[1];
        const curr = el[2];
        const remaining = el[3];

        const dist = bitDist[curr];

        let closed = prioSet & (~remaining);
        if (best[closed] < pressure) {
            best[closed] = pressure;
        }

        for (let i = 0; i < bitCount; i++) {
            let mask = 1 << i;
            if (!(remaining & mask)) continue;

            let newtime = time - dist[i] - 1;
            if (newtime > 0) {
                let newpressure = pressure + newtime * times[i];
                let newremaining = remaining & ~mask;
                paths.push([newtime, newpressure, i, newremaining]);
            }
        }
    }

    let partitions = [];
    for (let i = 0; i < best.length; i++) {
        const item = best[i];
        if (item != 0) {
            partitions.push([i, item]);
        }
    }

    partitions.sort((a, b) => b[1] - a[1]);

    let ans = 0;
    for (let a = 0; a < partitions.length; a++) {
        const i = partitions[a];
        let i0 = i[0];
        let i1 = i[1];

        for (let b = a + 1; b < partitions.length; b++) {
            const j = partitions[b];

            if (!(i0 & j[0]) && ans < i1 + j[1]) {
                ans = i1 + j[1];
            }
        }

        if (i1 < Math.floor(ans / 2)) {
            break;
        }
    }
    return ans;
}

import { checkAnswers } from "../test.js";
checkAnswers();
