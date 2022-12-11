import { getInput, arraySplit } from "../util.js";
const input = getInput();

const numbers = input[0].split(",").map(x => parseInt(x));
const boards = arraySplit(input.slice(1).map(x => arraySplit(x, 3).map(x => parseInt(x))), 5);

function testWin(b) {
    for (let i = 0; i < 5; i++) {
        let row = true;
        let col = true;
        for (let j = 0; j < 5; j++) {
            if (b[i][j] != -1) row = false;
            if (b[j][i] != -1) col = false;
        }
        if (row || col) return true;
    }
    return false;
}

function calcScore(board) {
    let sum = 0;
    for (const row of board) {
        for (let i = 0; i < 5; i++) {
            if (row[i] != -1) sum += row[i];
        }
    }
    return sum;
}

export function part1() {
    for (const num of numbers) {
        for (const board of boards) {
            for (const row of board) {
                for (let i = 0; i < 5; i++) {
                    if (row[i] == num) row[i] = -1;
                }
            }

            if (testWin(board)) {
                return calcScore(board) * num;
            }
        }
    }

    return -1;
}

export function part2() {
    let b = boards;

    for (const num of numbers) {
        for (const board of b) {
            for (const row of board) {
                for (let i = 0; i < 5; i++) {
                    if (row[i] == num) row[i] = -1;
                }
            }
        }

        if (b.length == 1) {
            if (testWin(b[0])) {
                return calcScore(b[0]) * num;
            }
        } else {
            b = b.filter(x => !testWin(x));
        }
    }

    return -1;
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
