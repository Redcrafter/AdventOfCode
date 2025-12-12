import { extractNumbers, getInput } from "../util.ts";

// const input = getInput();
const input = extractNumbers(getInput());

export function part1() {
    let max = 0;
    for (let i = 0; i < input.length; i++) {
        const [x1, y1] = input[i];

        for (let j = 0; j < input.length; j++) {
            const [x2, y2] = input[j];
            max = Math.max((Math.abs(x2 - x1) + 1) * (Math.abs(y2 - y1) + 1), max);
        }
    }

    return max;
}

export function part2() {
    // let str = "polygon(";
    // for (let i = 0; i < input.length; i++) {
    //     const [x1, y1] = input[i];
    //     str += `(${x1},${y1}),`;
    // }
    // console.log(str + ")");

    let max = 0;
    for (let i = 0; i < input.length; i++) {
        const [x1, y1] = input[i];

        for (let j = 0; j < input.length; j++) {
            const [x2, y2] = input[j];

            const dx = Math.abs(x2 - x1) + 1;
            const dy = Math.abs(y2 - y1) + 1;
            const area = dx * dy;
            if (area < max) continue;

            const l = Math.min(x1, x2);
            const r = Math.max(x1, x2);
            const b = Math.min(y1, y2);
            const t = Math.max(y1, y2);

            function contains(x, y) {
                return (l < x && x < r) && (b < y && y < t);
            }

            let valid = true;
            for (let k = 0; k < input.length; k++) {
                const [x3, y3] = input[k];

                if (contains(x3, y3)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;

            for (let k = 0; k < input.length; k++) {
                let [_x1, _y1] = input[k];
                const [_x2, _y2] = input[(k + 1) % input.length];

                const dx = Math.sign(_x2 - _x1);
                const dy = Math.sign(_y2 - _y1);

                if (dx == 0) {
                    while (_y1 != _y2) {
                        if (contains(_x1, _y1)) {
                            valid = false;
                            break;
                        }
                        _y1 += dy;
                    }
                } else {
                    if (b < _y1 && _y1 < t) {
                        if ((_x1 <= l && _x2 >= r) || (_x2 <= l && _x1 >= r)) {
                            valid = false;
                            break;
                        }
                    }

                    while (_x1 != _x2) {
                        if (contains(_x1, _y1)) {
                            valid = false;
                            break;
                        }
                        _x1 += dx;
                    }
                }
            }

            if (!valid) continue;
            max = Math.max(max, area);
        }
    }

    return max;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
