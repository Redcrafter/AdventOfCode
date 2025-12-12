import { getInput } from "../util.ts";

const input = getInput();
const input1 = input.slice(0, 50);
const input2 = input.slice(50).join("");

export function part1() {
    const height = input1.length;
    const width = input1[0].length;
    const inp = new Uint8Array(width * height);

    let x = 0;
    let y = 0;

    for (let y1 = 0; y1 < height; y1++) {
        for (let x1 = 0; x1 < width; x1++) {
            let c = input1[y1].charCodeAt(x1);
            if (c == 64) { // '@'
                x = x1;
                y = y1;
                c = 46; // '.'
            }
            inp[x1 + y1 * width] = c;
        }
    }

    function tryPush(x, y, dx, dy) {
        let cx = x + dx;
        let cy = y + dy;

        while (true) { // don't need oob checks
            const v = inp[cx + cy * width];
            if (v == 35) return false; // can't push
            if (v == 46) break;

            cx += dx;
            cy += dy;
        }
        while (cx != x + dx || cy != y + dy) {
            inp[cx + cy * width] = 79;
            cx -= dx;
            cy -= dy;
        }
        inp[cx + cy * width] = 46;
        return true;
    }

    for (let i = 0; i < input2.length; i++) {
        const dir = input2[i];

        if (dir == ">") {
            if (tryPush(x, y, 1, 0)) x++;
        } else if (dir == "<") {
            if (tryPush(x, y, -1, 0)) x--;
        } else if (dir == "^") {
            if (tryPush(x, y, 0, -1)) y--;
        } else if (dir == "v") {
            if (tryPush(x, y, 0, 1)) y++;
        }
    }

    let result = 0;
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (inp[x + y * width] == 79) // 'O' 
                result += x + y * 100;
        }
    }
    return result;
}

export function part2() {
    const height = input1.length;
    const width = input1[0].length * 2;

    const inp = new Uint8Array(width * height);
    let x = 0;
    let y = 0;

    for (let y1 = 0; y1 < input1.length; y1++) {
        for (let x1 = 0; x1 < input1[0].length; x1++) {
            let v = input1[y1].charCodeAt(x1);
            if (v == 79) { // 'O'
                inp[x1 * 2 + y1 * width] = 91; // '['
                inp[x1 * 2 + 1 + y1 * width] = 93; // ']'
                continue;
            }
            if (v == 64) { // '@'
                x = x1 * 2;
                y = y1;
                v = 46; // '.'
            }
            inp[x1 * 2 + y1 * width] = v;
            inp[x1 * 2 + 1 + y1 * width] = v;
        }
    }

    function tryPush(x, y, dx, dy, apply) {
        const curr = inp[x + y * width];
        if (curr == 35) return false;
        if (curr == 46) return true;

        if (dx != 0) { // left/right push
            if (tryPush(x + dx + dx, y, dx, dy, apply)) {
                if (apply) {
                    inp[(x + dx * 2) + y * width] = inp[(x + dx) + y * width];
                    inp[(x + dx) + y * width] = curr;
                    inp[x + y * width] = 46;
                }
                return true;
            }
        } else { // up/down push
            const adj = curr == 91 ? 1 : -1;
            if (tryPush(x, y + dy, dx, dy, apply) && tryPush(x + adj, y + dy, dx, dy, apply)) {
                if (apply) {
                    inp[x + (y + dy) * width] = inp[x + y * width];
                    inp[(x + adj) + (y + dy) * width] = inp[(x + adj) + y * width];

                    inp[x + y * width] = 46;
                    inp[(x + adj) + y * width] = 46;
                }
                return true;
            }
        }
        return false;
    }

    for (let i = 0; i < input2.length; i++) {
        const dir = input2[i];

        if (dir == ">") {
            if (tryPush(x + 1, y, 1, 0, false)) {
                tryPush(x + 1, y, 1, 0, true);
                x++;
            }
        } else if (dir == "<") {
            if (tryPush(x - 1, y, -1, 0, false)) {
                tryPush(x - 1, y, -1, 0, true);
                x--;
            }
        } else if (dir == "^") {
            if (tryPush(x, y - 1, 0, -1, false)) {
                tryPush(x, y - 1, 0, -1, true);
                y--;
            }
        } else if (dir == "v") {
            if (tryPush(x, y + 1, 0, 1, false)) {
                tryPush(x, y + 1, 0, 1, true);
                y++;
            }
        }
    }

    let result = 0;
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (inp[x + y * width] == 91)
                result += x + y * 100;
        }
    }
    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
