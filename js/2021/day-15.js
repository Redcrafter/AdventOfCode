import { getInput } from "../util.ts";

const input = getInput().map(x => [...x].map(y => parseInt(y)));

const _width = input[0].length;
const _height = input.length;

export function part1() {
    let width = input[0].length;
    let height = input.length;

    const w = width + 1;
    let riskMap = new Uint16Array((width + 1) * (height + 1));

    for (let y = 0; y <= height; y++) {
        riskMap[y * w] = 65535;
    }
    for (let x = 0; x <= width; x++) {
        riskMap[x] = 65535;
    }

    for (let y = 1; y <= height; y++) {
        for (let x = 1; x <= width; x++) {
            riskMap[x + y * w] = Math.min(riskMap[(x - 1) + y * w], riskMap[x + (y - 1) * w]) + input[y - 1][x - 1];
        }
    }

    return riskMap[riskMap.length - 1];
}

export function part2() {
    let width = _width * 5;
    let height = _height * 5;

    const w = width + 2;
    let riskMap = new Uint16Array((width + 2) * (height + 2));
    // riskMap.fill(65535);

    for (let i = 0; i < riskMap.length; i++) {
        riskMap[i] = 65535;
    }

    for (let i = 0; i < 5; i++) {
        for (let y = 1; y <= height; y++) {
            for (let x = 1; x <= width; x++) {
                let x1 = x - 1;
                let y1 = y - 1;

                let min = Math.min(riskMap[(x - 1) + y * w], riskMap[x + (y - 1) * w], riskMap[(x + 1) + y * w], riskMap[x + (y + 1) * w]);
                let val = ((input[y1 % _height][x1 % _width] + Math.floor(y1 / _height) + Math.floor(x1 / _width) - 1) % 9) + 1;
                val += min;

                riskMap[x + y * w] = val;
            }
        }
    }

    return riskMap[width + height * w];
}

import { checkAnswers } from "../test.ts";
checkAnswers();
