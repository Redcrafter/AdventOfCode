import { getInput } from "../util.js";
const input = getInput();

function getScore(c) {
    let code = c.charCodeAt(0);
    if (code >= 65 && code <= 90) {
        return code - 65 + 27
    } else {
        return code - 97 + 1;
    }
}

export function part1() {
    // return input.map(x => "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".indexOf([...x.slice(0, x.length / 2)].find(c => x.slice(x.length / 2).includes(c)))).reduce((a, b) => a + b, 0);
    // return sum(input.map(x => getScore([...x.slice(0, x.length / 2)].find(c => x.slice(x.length / 2).includes(c)))));
    let res = 0;

    for (const item of input) {
        for (let j = 0; j < item.length / 2; j++) {
            const c = item[j];

            if (item.includes(c, item.length / 2)) {
                res += getScore(c);
                break;
            }
        }
    }

    return res;
}

export function part2() {
    // return input.reduce((all, one, i) => { all[Math.floor(i / 3)] = [].concat((all[Math.floor(i / 3)] || []), one); return all }, []).map(x => "0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".indexOf([...x[0]].find(c => x[1].includes(c) && x[2].includes(c)))).reduce((a, b) => a + b, 0);
    // return sum(arraySplit(input, 3).map(x => getScore([...x[0]].find(c => x[1].includes(c) && x[2].includes(c)))));
    let res = 0;

    for (let i = 0; i < input.length; i += 3) {
        for (const c of input[i + 0]) {
            if (input[i + 1].includes(c) && input[i + 2].includes(c)) {
                res += getScore(c);
                break;
            }
        }
    }

    return res;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
