import { getInput } from "../util.js";
const input = getInput().map(x => x.split(/ \| | /));

export function part1() {
    let count = 0;
    function test(val) {
        count += val.length == 2 || val.length == 4 || val.length == 3 || val.length == 7;
    }
    for (const item of input) {
        test(item[10]);
        test(item[11]);
        test(item[12]);
        test(item[13]);
    }
    return count;
}

export function part2() {
    let sum = 0;

    function hasChar(a, b) {
        for (let i = 0; i < a.length; i++) {
            if (a.charCodeAt(i) == b) return true;
        }
        return false;
    }
    function hasCount(a, b) {
        let c = 0;
        for (let i = 0; i < b.length; i++) {
            if (hasChar(a, b.charCodeAt(i))) c++;
        }
        return c;
    }
    function hasAll(a, b) {
        for (let i = 0; i < b.length; i++) {
            if (!hasChar(a, b.charCodeAt(i))) return false;
        }
        return true;
    }

    for (const item of input) {
        let left = item.slice(0, 10);

        let one;
        let four;
        let seven;
        let eight;

        for (const x of left) {
            if (x.length == 2) one = x;
            if (x.length == 4) four = x;
            if (x.length == 3) seven = x;
            if (x.length == 7) eight = x;
        }

        let six = left.find(x => x.length == 6 && !hasAll(x, one));
        let nine = left.find(x => x.length == 6 && x !== six && hasAll(x, four));
        let three = left.find(x => x.length == 5 && hasAll(x, one));
        let two = left.find(x => x.length == 5 && x !== three && hasCount(x, nine) == 4);
        let five = left.find(x => x.length == 5 && x !== two && x != three);
        let zero = left.find(x => x.length == 6 && x != six && x !== nine);

        let digits = [
            zero,
            one,
            two,
            three,
            four,
            five,
            six,
            seven,
            eight,
            nine
        ];

        let num = 0;

        for (let i = 0; i < 4; i++) {
            const asdf = item[i + 10];

            if (asdf.length == 2) { num += (10 ** (3 - i)) * 1; continue; }
            if (asdf.length == 4) { num += (10 ** (3 - i)) * 4; continue; }
            if (asdf.length == 3) { num += (10 ** (3 - i)) * 7; continue; }
            if (asdf.length == 7) { num += (10 ** (3 - i)) * 8; continue; }

            for (let j = 0; j < 10; j++) {
                const d = digits[j];
                if (d.length == asdf.length && hasAll(d, asdf)) {
                    num += (10 ** (3 - i)) * j;
                    break;
                }
            }
        }

        sum += num;
    }

    return sum;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
