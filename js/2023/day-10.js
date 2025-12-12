import { getInput } from "../util.ts";

const input = getInput();

const width = input[0].length;

const top = 0;
const bottom = 1;
const left = 2;
const right = 3;

export function part1() {
    let start = null;

    for (let y = 0; y < input.length; y++) {
        let x = input[y].indexOf("S");
        if (x != -1) {
            start = [x, y];
            break;
        }
    }

    let starts = [];

    {
        const [x, y] = start;

        let t = input[y - 1]?.[x];
        if (t == "|" || t == "7" || t == "F")
            starts.push([x, y - 1, bottom]);

        let b = input[y + 1]?.[x];
        if (b == "|" || b == "L" || b == "J")
            starts.push([x, y + 1, top]);

        let l = input[y][x - 1];
        if (l == "-" || l == "L" || l == "F")
            starts.push([x - 1, y, right]);

        let r = input[y][x + 1];
        if (r == "-" || r == "J" || r == "7")
            starts.push([x + 1, y, left]);
    }

    let i = 2;
    while (true) {
        let [x, y, from] = starts[i & 1];

        if (starts[0][0] == starts[1][0] && starts[0][1] == starts[1][1]) {
            return Math.ceil(i / 2);
        }

        const s = input[y][x];

        if (s == "|") {
            if (from == top) {
                y++;
                from = top;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "-") {
            if (from == left) {
                x++;
                from = left;
            } else {
                x--;
                from = right;
            }
        } else if (s == "L") {
            if (from == top) {
                x++;
                from = left;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "J") {
            if (from == top) {
                x--;
                from = right;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "7") {
            if (from == bottom) {
                x--;
                from = right;
            } else {
                y++;
                from = top;
            }
        } else if (s == "F") {
            if (from == bottom) {
                x++;
                from = left;
            } else {
                y++;
                from = top;
            }
        }

        starts[i & 1] = [x, y, from];
        i++;
    }
}

export function part2_flood() {
    let start = null;
    let known = new Map();

    for (let y = 0; y < input.length; y++) {
        let x = input[y].indexOf("S");
        if (x != -1) {
            start = [x, y];
            break;
        }
    }

    let starts = [];

    {
        const [x, y] = start;
        known.set(x + y * width * 4, 0);

        let t = input[y - 1]?.[x];
        if (t == "|" || t == "7" || t == "F") {
            known.set((x) + (y - 0.5) * width * 4, 0.5);
            starts.push([x, y - 1, bottom]);
        }

        let b = input[y + 1]?.[x];
        if (b == "|" || b == "L" || b == "J") {
            known.set((x) + (y + 0.5) * width * 4, 0.5);
            starts.push([x, y + 1, top]);
        }

        let l = input[y][x - 1];
        if (l == "-" || l == "L" || l == "F") {
            known.set((x - 0.5) + (y) * width * 4, 0.5);
            starts.push([x - 1, y, right]);
        }

        let r = input[y][x + 1];
        if (r == "-" || r == "J" || r == "7") {
            known.set((x + 0.5) + (y) * width * 4, 0.5);
            starts.push([x + 1, y, left]);
        }
    }

    for (let [x, y, from] of starts) {
        let t = 1;

        while (true) {
            const s = input[y][x];

            let id = x + y * width * 4;
            if (known.get(id) <= t)
                break;
            known.set(id, t);

            if (s == "|") {
                if (from == top) {
                    known.set((x) + (y + 0.5) * width * 4, t + 0.5);
                    y++;
                    from = top;
                } else {
                    known.set((x) + (y - 0.5) * width * 4, t + 0.5);
                    y--;
                    from = bottom;
                }
            } else if (s == "-") {
                if (from == left) {
                    known.set((x + 0.5) + (y) * width * 4, t + 0.5);
                    x++;
                    from = left;
                } else {
                    known.set((x - 0.5) + (y) * width * 4, t + 0.5);
                    x--;
                    from = right;
                }
            } else if (s == "L") {
                if (from == top) {
                    known.set((x + 0.5) + (y) * width * 4, t + 0.5);
                    x++;
                    from = left;
                } else {
                    known.set((x) + (y - 0.5) * width * 4, t + 0.5);
                    y--;
                    from = bottom;
                }
            } else if (s == "J") {
                if (from == top) {
                    known.set((x - 0.5) + (y) * width * 4, t + 0.5);
                    x--;
                    from = right;
                } else {
                    known.set((x) + (y - 0.5) * width * 4, t + 0.5);
                    y--;
                    from = bottom;
                }
            } else if (s == "7") {
                if (from == bottom) {
                    known.set((x - 0.5) + (y) * width * 4, t + 0.5);
                    x--;
                    from = right;
                } else {
                    known.set((x) + (y + 0.5) * width * 4, t + 0.5);
                    y++;
                    from = top;
                }
            } else if (s == "F") {
                if (from == bottom) {
                    known.set((x + 0.5) + (y) * width * 4, t + 0.5);
                    x++;
                    from = left;
                } else {
                    known.set((x) + (y + 0.5) * width * 4, t + 0.5);
                    y++;
                    from = top;
                }
            }
            t++;
        }
    }

    let outside = new Set();
    let stack = [[-0.5, -0.5]];

    while (stack.length > 0) {
        let [x, y] = stack.pop();
        let id = x + y * width * 4;
        if (outside.has(id)) continue
        outside.add(id);

        if (!known.has(x + y * width * 4)) {
            if (x <= width) stack.push([x + 0.5, y]);
            if (x > 0) stack.push([x - 0.5, y]);
            if (y <= input.length) stack.push([x, y + 0.5]);
            if (y > 0) stack.push([x, y - 0.5]);
        }

    }
    // print();
    // console.log();

    let m = 0;

    for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < width; x++) {
            let id = x + y * width * 4;
            if (!outside.has(id) && !known.has(id)) m++;
        }
    }
    return m;
}

export function part2() {
    let start = null;
    for (let y = 0; y < input.length; y++) {
        let x = input[y].indexOf("S");
        if (x != -1) {
            start = [x, y];
            break;
        }
    }

    let starts = [];

    const [sx, sy] = start;
    {
        let t = input[sy - 1]?.[sx];
        if (t == "|" || t == "7" || t == "F")
            starts.push([sx, sy - 1, bottom]);

        let b = input[sy + 1]?.[sx];
        if (b == "|" || b == "L" || b == "J")
            starts.push([sx, sy + 1, top]);

        let l = input[sy][sx - 1];
        if (l == "-" || l == "L" || l == "F")
            starts.push([sx - 1, sy, right]);

        let r = input[sy][sx + 1];
        if (r == "-" || r == "J" || r == "7")
            starts.push([sx + 1, sy, left]);
    }


    let m = 0;
    let c = 0;

    let lx = sx;
    let ly = sy;
    let x = starts[0][0];
    let y = starts[0][1];
    let from = starts[0][2];

    while (true) {
        m += (ly + y) * (lx - x);
        lx = x;
        ly = y;
        c++;

        const s = input[y][x];
        if (x == sx && y == sy)
            break;

        if (s == "|") {
            if (from == top) {
                y++;
                from = top;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "-") {
            if (from == left) {
                x++;
                from = left;
            } else {
                x--;
                from = right;
            }
        } else if (s == "L") {
            if (from == top) {
                x++;
                from = left;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "J") {
            if (from == top) {
                x--;
                from = right;
            } else {
                y--;
                from = bottom;
            }
        } else if (s == "7") {
            if (from == bottom) {
                x--;
                from = right;
            } else {
                y++;
                from = top;
            }
        } else if (s == "F") {
            if (from == bottom) {
                x++;
                from = left;
            } else {
                y++;
                from = top;
            }
        }
    }

    // https://en.wikipedia.org/wiki/Shoelace_formula
    // https://en.wikipedia.org/wiki/Pick's_theorem
    return Math.abs(m / 2) - (c / 2) + 1;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
