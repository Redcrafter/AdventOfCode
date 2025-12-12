import { getInput } from "../util.ts";

const input = [...getInput()[0]].map(x => parseInt(x));

// sum formula return 0 + 1 + 2 + 3 + 4 + ... + n
function triangle(n) {
    return (n * (n + 1)) / 2;
}

export function part1() {
    let result = 0;

    let lIndex = 0;
    let rIndex = input.length - 1;
    let lGap = 0;

    let rVal = 0;
    let rSize = 0;

    let ind = 0;

    function add(value, times) {
        result += value * (triangle(ind + times - 1) - triangle(ind - 1));
        ind += times;
    }

    while (lIndex < rIndex) {
        if (lGap == 0) { // ran out of gap
            add(lIndex / 2, input[lIndex]);
            lIndex++;

            lGap = input[lIndex];
            lIndex++;
        }
        if (rSize == 0) { // ran out of right value
            rSize = input[rIndex];
            rVal = rIndex / 2;
            rIndex -= 2;
        }

        const n = Math.min(rSize, lGap);
        add(rVal, n);
        rSize -= n;
        lGap -= n;
    }

    add(lIndex / 2, input[lIndex]);
    add(rVal, rSize);

    return result;
}

export function part2() {
    const gaps = Array.from({ length: 10 }, () => []);

    let size = 0;
    for (let i = 0; i < input.length;) {
        size += input[i];
        i++;
        if (i >= input.length) break;

        const g = input[i];
        i++;
        if (g == 0) continue;

        gaps[g].push(size);
        size += g;
    }

    for (const el of gaps) el.reverse();

    let result = 0;
    function add(value, times, ind) {
        result += value * (triangle(ind + times - 1) - triangle(ind - 1));
    }

    let i = input.length - 1;
    let offset = size;
    while (i >= 0) {
        const size = input[i];
        offset -= size;
        const nOffset = offset;
        const val = i / 2;
        i--;

        if (i >= 0) {
            offset -= input[i];
            i--;
        }
        if (size == 0) continue;

        let minG = 1 << 30;
        let minGapSize = -1;

        for (let j = size; j < gaps.length; j++) {
            const g = gaps[j];
            if (g.length == 0) continue;
            const gi = g[g.length - 1];

            if (gi < minG) {
                minG = gi;
                minGapSize = j;
            }
        }

        if (minGapSize == -1 || minG > nOffset) {
            add(val, size, nOffset);
        } else {
            add(val, size, minG);

            gaps[minGapSize].pop();
            if (minGapSize > size) {
                const g = gaps[minGapSize - size];
                const p = minG + size;

                g.push(p);
                for (let i = g.length - 2; i >= 0; i--) {

                    if (g[i] > p) {
                        g[i + 1] = p;
                        break;
                    } else {
                        g[i + 1] = g[i];
                    }
                }
            }
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
