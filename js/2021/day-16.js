
import { getInput } from "../util.js";

const input = getInput()[0];

function toBits() {
    let bits = [];

    for (const c of input) {
        switch (c) {
            case '0': bits.push(0, 0, 0, 0); break;
            case '1': bits.push(0, 0, 0, 1); break;
            case '2': bits.push(0, 0, 1, 0); break;
            case '3': bits.push(0, 0, 1, 1); break;
            case '4': bits.push(0, 1, 0, 0); break;
            case '5': bits.push(0, 1, 0, 1); break;
            case '6': bits.push(0, 1, 1, 0); break;
            case '7': bits.push(0, 1, 1, 1); break;
            case '8': bits.push(1, 0, 0, 0); break;
            case '9': bits.push(1, 0, 0, 1); break;
            case 'A': bits.push(1, 0, 1, 0); break;
            case 'B': bits.push(1, 0, 1, 1); break;
            case 'C': bits.push(1, 1, 0, 0); break;
            case 'D': bits.push(1, 1, 0, 1); break;
            case 'E': bits.push(1, 1, 1, 0); break;
            case 'F': bits.push(1, 1, 1, 1); break;
        }
    }

    return bits;
}

export function part1() {
    let bits = toBits();

    function take(b) {
        let res = 0;
        for (let i = 0; i < b; i++) {
            res <<= 1;
            res |= bits.shift();
        }
        return res;
    }

    let sum = 0;
    function takePacket() {
        let id = take(3);
        let type = take(3);

        sum += id;

        switch (type) {
            case 4: {
                let num = 0;

                while (bits[0] != 0) {
                    bits.shift();
                    num <<= 4;
                    num |= take(4);
                }
                bits.shift();
                num <<= 4;
                num |= take(4);
                
                break;
            }
            default: {
                let lengthTypeID = take(1);

                if(lengthTypeID == 0) {
                    let length = take(15);
                    let pos = bits.length;
                    while (pos - bits.length < length) {
                        takePacket();
                    }
                } else {
                    let count = take(11);
                    for (let i = 0; i < count; i++) {
                        takePacket();
                    }
                }
            }
        }
    }
    takePacket();

    return sum;
}

export function part2() {
    let bits = toBits();

    function take(b) {
        let res = 0;
        for (let i = 0; i < b; i++) {
            res <<= 1;
            res |= bits.shift();
        }
        return res;
    }

    function takePacket() {
        let id = take(3);
        let type = take(3);

        switch (type) {
            case 4: {
                let num = 0;

                while (take(1) != 0) {
                    num = (num * 16) + take(4);
                }
                num = (num * 16) + take(4);
                
                return num;
            }
            default: {
                let lengthTypeID = take(1);

                let vals = [];
                if(lengthTypeID == 0) {
                    let length = take(15);
                    let pos = bits.length;
                    while (pos - bits.length < length) {
                        vals.push(takePacket());
                    }
                } else {
                    let count = take(11);
                    for (let i = 0; i < count; i++) {
                        vals.push(takePacket());
                    }
                }

                switch (type) {
                    case 0: return vals.reduce((p, c) => p + c, 0);
                    case 1: return vals.reduce((p, c) => p * c, 1);
                    case 2: return vals.reduce((p, c) => Math.min(p, c), Infinity);
                    case 3: return vals.reduce((p, c) => Math.max(p, c), 0);
                    case 5: return (vals[0] > vals[1]) + 0;
                    case 6: return (vals[0] < vals[1]) + 0;
                    case 7: return (vals[0] == vals[1]) + 0;
                    default: throw type;
                }
            }
        }
    }

    let val = takePacket();
    return val;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
