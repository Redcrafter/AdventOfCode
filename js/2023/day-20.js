import { getInput } from "../util.js";

const input = getInput();

const low = 0;
const high = 1;

export function part1() {
    let map = new Map();
    let targets;

    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split(" -> ");

        if (a[0] == "&") {
            map.set(a.substring(1), {
                type: "and",
                memory: new Map(),
                dest: b.split(", ")
            });
        } else if (a[0] == "%") {
            map.set(a.substring(1), {
                type: "ff",
                on: false,
                dest: b.split(", ")
            });
        } else {
            targets = b.split(", ");
        }
    }

    for (const [k, v] of map) {
        for (const d of v.dest) {
            let t = map.get(d);
            if (t?.type == "and") {
                t.memory.set(k, low);
            }
        }
    }

    let lc = 0;
    let hc = 0;

    for (let j = 0; j < 1000; j++) {
        lc++;
        let stack = [];
        for (const thing of targets) {
            stack.push([thing, low, "broadcaster"])
        }

        for (let i = 0; i < stack.length; i++) {
            let [t, pulse, src] = stack[i];

            if (pulse == low) lc++;
            else hc++;

            let el = map.get(t);

            if (el?.type == "and") {
                el.memory.set(src, pulse);

                if ([...el.memory].every(x => x[1] == high)) {
                    for (const sub of el.dest) {
                        stack.push([sub, low, t]);
                    }
                } else {
                    for (const sub of el.dest) {
                        stack.push([sub, high, t]);
                    }
                }

            } else if (el?.type == "ff") {
                if (pulse == low) {
                    el.on = !el.on;
                    for (const sub of el.dest) {
                        stack.push([sub, el.on ? high : low, t]);
                    }
                }
            }

        }
    }

    return lc * hc;
}

export function part2() {
    let map = new Map();
    let targets;
    let ends = new Set();
    let src;

    for (let i = 0; i < input.length; i++) {
        const [a, b] = input[i].split(" -> ");

        if (a[0] == "&") {
            map.set(a.substring(1), {
                type: "and",
                memory: new Map(),
                dest: b.split(", "),
                src: []
            });
            // cycles.set(a.substring(1), []);
        } else if (a[0] == "%") {
            map.set(a.substring(1), {
                type: "ff",
                on: false,
                dest: b.split(", "),
                src: []
            });
        } else {
            targets = b.split(", ");
        }

        if (b == "rx")
            src = a.substring(1);
    }

    for (const [k, v] of map) {
        for (const d of v.dest) {
            let t = map.get(d);
            if (t?.type == "and") {
                t.memory.set(k, low);
            }
            if (d == src)
                ends.add(k);
        }
    }

    let vals = [];
    for (let j = 1; vals.length != ends.size; j++) {
        let stack = [];
        for (const thing of targets) {
            stack.push([thing, low, "broadcaster"])
        }

        for (let i = 0; i < stack.length; i++) {
            let [t, pulse, src] = stack[i];

            let el = map.get(t);

            if (el?.type == "and") {
                el.memory.set(src, pulse);

                if ([...el.memory].every(x => x[1] == high)) {
                    for (const sub of el.dest) {
                        stack.push([sub, low, t]);
                    }
                } else {
                    for (const sub of el.dest) {
                        stack.push([sub, high, t]);
                    }

                    if (ends.has(t)) {
                        vals.push(j);
                    }
                }
            } else if (el?.type == "ff") {
                if (pulse == low) {
                    el.on = !el.on;
                    for (const sub of el.dest) {
                        stack.push([sub, el.on ? high : low, t]);
                    }
                }
            }

        }
    }

    return vals[0] * vals[1] * vals[2] * vals[3];
}

import { checkAnswers } from "../test.js";
checkAnswers();
