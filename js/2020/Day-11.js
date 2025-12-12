import { getInput, sum } from "../util.ts";

const input = getInput().map(x => [...x].map(y => y == "." ? 0 : (y == "L" ? 1 : 2)));

export function part1() {
    let curr = new Uint8Array(input.flatMap(x => x));
    let next = curr.slice();

    const height = input.length;
    const width = input[0].length;

    function any(x, y) {
        
        let i = x + y * width;
        let l = x > 0;
        let r = x + 1 < width;
        
        let t = y > 0;
        let b = y + 1 < height;
        
       return (
           t && l && curr[i - width - 1] == 2 ||
           t && curr[i - width] == 2 ||
           t && r && curr[i - width + 1] == 2 ||
           r && curr[i + 1] == 2 ||
           b && r && curr[i + width + 1] == 2 ||
           b && curr[i + width] == 2 ||
           b && l && curr[i + width - 1] == 2 ||
           l && curr[i - 1] == 2
       )
    }

    function coutN(x, y) {
        let s = 0;

        let i = x + y * width;
        let l = x > 0;
        let r = x + 1 < width;

        let t = y > 0;
        let b = y + 1 < height;

        s += t && l && curr[i - width - 1] == 2;
        s += t && curr[i - width] == 2;
        s += t && r && curr[i - width + 1] == 2;
        s += r && curr[i + 1] == 2;
        s += b && r && curr[i + width + 1] == 2;
        s += b && curr[i + width] == 2;
        s += b && l && curr[i + width - 1] == 2;
        s += l && curr[i - 1] == 2;

        return s;
    }

    while (true) {
        let changed = false;

        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                const v = curr[x + y * width];
                next[x + y * width] = v;

                if (v == 1) {
                    if (!any(x, y)) {
                        next[x + y * width] = 2;
                        changed = true;
                    }
                } else if (v == 2) {
                    if (coutN(x, y) >= 4) {
                        next[x + y * width] = 1;
                        changed = true;
                    }
                }

            }
        }

        if (!changed) {
            return sum(next.map(x => x == 2))
        }

        [curr, next] = [next, curr];
    }
}

export function part2() {
    let curr = new Uint8Array(input.flatMap(x => x));
    let next = curr.slice();

    const height = input.length;
    const width = input[0].length;

    let offsets = new Array(width * height);
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            let asd = [];

            function ray(x, y, dx, dy) {
                while (true) {
                    x += dx;
                    y += dy;

                    if (x < 0 || x >= width || y < 0 || y >= height)
                        return;

                    if (curr[x + y * width] != 0) {
                        asd.push(x + y * width);
                        return;
                    }
                }
            }

            ray(x, y, -1, -1)
            ray(x, y, -1, 0)
            ray(x, y, -1, 1)
            ray(x, y, 0, -1)
            ray(x, y, 0, 1)
            ray(x, y, 1, -1)
            ray(x, y, 1, 0)
            ray(x, y, 1, 1)

            offsets[x + y * width] = asd;
        }
    }

    function any(ind) {
        let as = offsets[ind];
        for (let i = 0; i < as.length; i++) {
            if (curr[as[i]] == 2) return false;
        }
        return true;
    }

    function countN(ind) {
        let as = offsets[ind];

        let s = 0;
        for (let i = 0; i < as.length; i++) {
            s += curr[as[i]] == 2;
        }
        return s;
    }

    while (true) {
        let changed = false;

        for (let i = 0; i < curr.length; i++) {
            const v = curr[i];

            if (v == 1) {
                if (any(i)) {
                    next[i] = 2;
                    changed = true;
                } else {
                    next[i] = 1;
                }
            } else if (v == 2) {
                if (countN(i) >= 5) {
                    next[i] = 1;
                    changed = true;
                } else {
                    next[i] = 2;
                }
            }
        }

        if (!changed) {
            return sum(next.map(x => x == 2));
        }

        [curr, next] = [next, curr];
    }
}


import { checkAnswers } from "../test.ts";
checkAnswers();
