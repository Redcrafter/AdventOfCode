import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput());

function calc(blue, T) {
    const maxOre = Math.max(blue[1], blue[2], blue[3], blue[5]);
    const queue = [[0, 0, 0, 0, 1, 0, 0, 0, T]];
    let maxGeode = 0;

    while (queue.length) {
        const el = queue.pop();
        const ore = el[0];
        const clay = el[1];
        const obsidian = el[2];
        const geode = el[3];
        const oreRobot = el[4];
        const clayRobot = el[5];
        const obsidianRobot = el[6];
        const geodeRobot = el[7];
        const time = el[8];
        maxGeode = Math.max(maxGeode, geode + geodeRobot * time);

        if (obsidianRobot != 0) {
            let until = Math.max(Math.ceil((blue[5] - ore) / oreRobot), Math.ceil((blue[6] - obsidian) / obsidianRobot)) + 1;
            if (until < 1) until = 1;

            let left = time - until;
            if (time >= until && geode + geodeRobot * time + left + (left * (left - 1)) / 2 >= maxGeode) {
                queue.push([
                    ore + oreRobot * until - blue[5],
                    clay + clayRobot * until,
                    obsidian + obsidianRobot * until - blue[6],
                    geode + geodeRobot * until,
                    oreRobot,
                    clayRobot,
                    obsidianRobot,
                    geodeRobot + 1,
                    time - until
                ]);
            }
        }

        if (clayRobot != 0 && obsidianRobot < blue[6]) {
            let until = Math.max(Math.ceil((blue[3] - ore) / oreRobot), Math.ceil((blue[4] - clay) / clayRobot)) + 1;
            if (until < 1) until = 1;

            let left = time - until;
            if (time >= until && geode + geodeRobot * time + (left * (left - 1)) / 2 >= maxGeode)
                queue.push([
                    ore + oreRobot * until - blue[3],
                    clay + clayRobot * until - blue[4],
                    obsidian + obsidianRobot * until,
                    geode + geodeRobot * until,
                    oreRobot,
                    clayRobot,
                    obsidianRobot + 1,
                    geodeRobot,
                    time - until
                ]);
        }

        if (clayRobot < blue[4]) {
            let until = Math.ceil((blue[2] - ore) / oreRobot) + 1;
            if (until < 1) until = 1;

            let left = time - until;
            if (time >= until && geode + geodeRobot * time + (left * (left - 1)) / 2 >= maxGeode)
                queue.push([
                    ore + oreRobot * until - blue[2],
                    clay + clayRobot * until,
                    obsidian + obsidianRobot * until,
                    geode + geodeRobot * until,
                    oreRobot,
                    clayRobot + 1,
                    obsidianRobot,
                    geodeRobot,
                    time - until
                ]);
        }

        if (oreRobot < maxOre) {
            let until = Math.ceil((blue[1] - ore) / oreRobot) + 1;
            if (until < 1) until = 1;

            let left = time - until;
            if (time >= until && geode + geodeRobot * time + (left * (left - 1)) / 2 >= maxGeode)
                queue.push([
                    ore + oreRobot * until - blue[1],
                    clay + clayRobot * until,
                    obsidian + obsidianRobot * until,
                    geode + geodeRobot * until,
                    oreRobot + 1,
                    clayRobot,
                    obsidianRobot,
                    geodeRobot,
                    time - until
                ]);
        }
    }

    return maxGeode;
}

export function part1() {
    let res = 0;
    for (const item of input) {
        res += item[0] * calc(item, 24);
    }
    return res;
}

export function part2() {
    return calc(input[0], 32) * calc(input[1], 32) * calc(input[2], 32)
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
