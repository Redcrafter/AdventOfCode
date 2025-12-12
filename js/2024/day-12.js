import { getInput } from "../util.ts";

const input_ = getInput();
const input = new Uint8Array([...input_.join("")].map(x => x.charCodeAt(0)));

const height = input_.length;
const width = input_[0].length;

export function part1() {
    let result = 0;

    const visited = new Uint8Array(width * height);
    const inner = new Uint8Array(width * height);

    function rec(x, y, c) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return 1 << 16;
        }
        if (inner[x + y * width]) return 0;

        if (input[x + y * width] == c) {
            inner[x + y * width] = 1;
            visited[x + y * width] = 1;

            return rec(x - 1, y, c) +
                rec(x, y + 1, c) +
                rec(x, y - 1, c) +
                rec(x + 1, y, c) + 1;
        }
        return 1 << 16;
    }

    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (visited[x + y * width]) continue;
            const c = input[x + y * width];

            inner.fill(0);
            const v = rec(x, y, c, inner);

            result += (v & 0xFFFF) * (v >> 16);
        }
    }

    return result;
}

export function part2() {
    let result = 0;

    const visited = new Uint32Array(width * height);
    const inner = new Uint8Array(width * height);
    const edges = new Set();

    function rec2(x, y, c) {
        if (x < 0 || x >= width || y < 0 || y >= height) return 0;
        if (inner[x + y * width]) return 0;

        if (input[x + y * width] == c) {
            inner[x + y * width] = 1;
            visited[x + y * width] = 1;

            if (x == 0 || input[(x - 1) + y * width] != c) { // left
                edges.add(((x + y * width) << 2) | 0);
            }
            if (x + 1 == width || input[(x + 1) + y * width] != c) { // right
                edges.add(((x + y * width) << 2) | 1);
            }
            if (y == 0 || input[x + (y - 1) * width] != c) {
                edges.add(((x + y * width) << 2) | 2); // top
            }
            if (y + 1 == height || input[x + (y + 1) * width] != c) {
                edges.add(((x + y * width) << 2) | 3); // bottom
            }

            return rec2(x - 1, y, c) +
                rec2(x, y + 1, c) +
                rec2(x, y - 1, c) +
                rec2(x + 1, y, c) + 1;
        } else {
            inner[x + y * width] = 1;
        }
        return 0;
    }

    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            if (visited[x + y * width]) continue;
            const c = input[x + y * width];

            inner.fill(0);
            edges.clear();
            const area = rec2(x, y, c);

            let corners = 0;
            for (const el of edges) {
                const dir = el & 3;
                const y = ((el >> 2) / width) | 0;
                const x = (el >> 2) % width;

                if (dir == 2 && !edges.has(((x + 1 + y * width) << 2) | 2))
                    corners++;
                if (dir == 3 && !edges.has(((x + 1 + y * width) << 2) | 3))
                    corners++;
                if (dir == 0 && !edges.has(((x + (y + 1) * width) << 2) | 0))
                    corners++;
                if (dir == 1 && !edges.has(((x + (y + 1) * width) << 2) | 1))
                    corners++;
            }

            result += area * corners;
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
