import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    let stack = [];
    for (let i = 0; i < 500; i++) {
        stack.push(new Array(100).fill(0));
    }

    function set(p0, p1, v) {
        let [x0, y0, z0] = p0;
        let [x1, y1, z1] = p1;

        let deltaX = Math.sign(x1 - x0);
        let deltaY = Math.sign(y1 - y0);
        let deltaZ = Math.sign(z1 - z0);

        while (x0 != x1 || y0 != y1 || z0 != z1) {
            stack[z0][x0 + y0 * 10] = v;

            x0 += deltaX;
            y0 += deltaY;
            z0 += deltaZ;
        }
        stack[z0][x0 + y0 * 10] = v;
    }
    function overlap(p0, p1) {
        let [x0, y0, z0] = p0;
        let [x1, y1, z1] = p1;

        let deltaX = Math.sign(x1 - x0);
        let deltaY = Math.sign(y1 - y0);
        let deltaZ = Math.sign(z1 - z0);

        while (x0 != x1 || y0 != y1 || z0 != z1) {
            if (stack[z0][x0 + y0 * 10] != 0) {
                return true;
            }
            x0 += deltaX;
            y0 += deltaY;
            z0 += deltaZ;
        }
        if (stack[z0][x0 + y0 * 10] != 0) {
            return true;
        }
        return false;
    }
    function canFall(x, y, z) {
        let ind = stack[z][x + y * 10];
        if (ind == 0)
            return false;

        let [p0, p1] = stuff[ind - 1];
        set(p0, p1, 0);

        p0[2]--;
        p1[2]--;

        if (overlap(p0, p1)) {
            p0[2]++;
            p1[2]++;

            set(p0, p1, ind);
            return false;
        }
        p0[2]++;
        p1[2]++;
        set(p0, p1, ind);
        return true;
    }
    function asd(p0, p1, v) {
        set(p0, p1, 0);

        let [x0, y0, z0] = p0;
        let [x1, y1, z1] = p1;

        let deltaX = Math.sign(x1 - x0);
        let deltaY = Math.sign(y1 - y0);
        let deltaZ = Math.sign(z1 - z0);

        while (x0 != x1 || y0 != y1 || z0 != z1) {
            if (canFall(x0, y0, z0 + 1)) {
                set(p0, p1, v);
                return false;
            }

            x0 += deltaX;
            y0 += deltaY;
            z0 += deltaZ;
        }
        if (canFall(x0, y0, z0 + 1)) {
            set(p0, p1, v);
            return false;
        }
        set(p0, p1, v);
        return true;
    }

    let stuff = [];

    for (let i = 0; i < input.length; i++) {
        let [start, end] = input[i].split("~");
        let p0 = start.split(",").map(x => parseInt(x));
        let p1 = end.split(",").map(x => parseInt(x));
        stuff.push([p0, p1]);
    }

    stuff.sort((a, b) => a[0][2] - b[0][2]);

    for (let i = 0; i < stuff.length; i++) {
        const [p0, p1] = stuff[i];

        while (p0[2] > 1) {
            p0[2]--;
            p1[2]--;

            if (overlap(p0, p1)) {
                p0[2]++;
                p1[2]++;
                break;
            }
        }

        set(p0, p1, i + 1);
    }

    let res = 0;
    for (let i = 0; i < stuff.length; i++) {
        const [p0, p1] = stuff[i];

        if (asd(p0, p1, i + 1)) {
            res++;
        }
    }
    return res;
}

export function part2() {
    let stack = [];
    for (let i = 0; i < 500; i++) {
        stack.push(new Array(100).fill(0));
    }

    function set(p0, p1, v) {
        let [x0, y0, z0] = p0;
        let [x1, y1, z1] = p1;

        let deltaX = Math.sign(x1 - x0);
        let deltaY = Math.sign(y1 - y0);
        let deltaZ = Math.sign(z1 - z0);

        while (x0 != x1 || y0 != y1 || z0 != z1) {
            stack[z0][x0 + y0 * 10] = v;

            x0 += deltaX;
            y0 += deltaY;
            z0 += deltaZ;
        }
        stack[z0][x0 + y0 * 10] = v;
    }
    function overlap(p0, p1) {
        let [x0, y0, z0] = p0;
        let [x1, y1, z1] = p1;

        let deltaX = Math.sign(x1 - x0);
        let deltaY = Math.sign(y1 - y0);
        let deltaZ = Math.sign(z1 - z0);

        while (x0 != x1 || y0 != y1 || z0 != z1) {
            if (stack[z0][x0 + y0 * 10] != 0) {
                return true;
            }
            x0 += deltaX;
            y0 += deltaY;
            z0 += deltaZ;
        }
        if (stack[z0][x0 + y0 * 10] != 0) {
            return true;
        }
        return false;
    }
    function canFall(x, y, z) {
        let ind = stack[z][x + y * 10];
        if (ind == 0)
            return false;

        let [p0, p1] = stuff[ind - 1];
        set(p0, p1, 0);

        p0[2]--;
        p1[2]--;

        if (overlap(p0, p1)) {
            p0[2]++;
            p1[2]++;

            set(p0, p1, ind);
            return false;
        }
        p0[2]++;
        p1[2]++;
        set(p0, p1, ind);
        return true;
    }
    function countFall(v) {
        let queue = [v];
        let seen = new Set();

        for (let i = 0; i < queue.length; i++) {
            const v = queue[i];
            let [p0, p1] = stuff[v - 1];
            set(p0, p1, 0);

            if (seen.has(v))
                continue;
            seen.add(v);

            let [x0, y0, z0] = p0;
            let [x1, y1, z1] = p1;
            let deltaX = Math.sign(x1 - x0);
            let deltaY = Math.sign(y1 - y0);
            let deltaZ = Math.sign(z1 - z0);

            while (x0 != x1 || y0 != y1 || z0 != z1) {
                if (canFall(x0, y0, z0 + 1)) {
                    queue.push(stack[z0 + 1][x0 + y0 * 10]);
                }

                x0 += deltaX;
                y0 += deltaY;
                z0 += deltaZ;
            }
            if (canFall(x0, y0, z0 + 1)) {
                queue.push(stack[z0 + 1][x0 + y0 * 10]);
            }
        }

        // re create the stack
        for (const v of queue) {
            let [p0, p1] = stuff[v - 1];
            set(p0, p1, v);
        }

        seen.delete(v);
        return seen.size;
    }

    let stuff = [];

    for (let i = 0; i < input.length; i++) {
        let [start, end] = input[i].split("~");
        let p0 = start.split(",").map(x => parseInt(x));
        let p1 = end.split(",").map(x => parseInt(x));
        stuff.push([p0, p1]);
    }

    stuff.sort((a, b) => a[0][2] - b[0][2]);

    for (let i = 0; i < stuff.length; i++) {
        const [p0, p1] = stuff[i];

        while (p0[2] > 1) {
            p0[2]--;
            p1[2]--;

            if (overlap(p0, p1)) {
                p0[2]++;
                p1[2]++;
                break;
            }
        }

        set(p0, p1, i + 1);
    }

    let res = 0;
    for (let i = 0; i < stuff.length; i++) {
        res += countFall(i + 1);
    }

    return res;
}

import { checkAnswers } from "../test.js";
checkAnswers();
