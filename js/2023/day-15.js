import { getInput, sum } from "../util.js";

const input = getInput()[0].split(",");

function hash(line) {
    let hash = 0;

    for (let i = 0; i < line.length; i++) {
        const c = line.charCodeAt(i);
        hash += c;
        hash *= 17;
        hash = hash % 256;
    }
    return hash;
}

export function part1() {
    return sum(input.map(hash));
}

export function part2() {
    let result = 0;

    let boxes = new Array(256);
    for (let i = 0; i < 256; i++) {
        boxes[i] = new Map();
    }

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        if (line.includes("=")) {
            let [a, b] = line.split("=");
            boxes[hash(a)].set(a, b);
        } else {
            let label = line.substring(0, line.length - 1);
            boxes[hash(label)].delete(label);
        }
    }

    for (let i = 0; i < boxes.length; i++) {
        const box = boxes[i];

        let asd = [...box];
        for (let j = 0; j < asd.length; j++) {
            const [a, b] = asd[j];
            result += (i + 1) * (j + 1) * parseInt(b);
        }
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
