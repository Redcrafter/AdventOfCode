import { getInput } from "../util.js";

const input = getInput();

const player1 = parseInt(input[0][28]);
const player2 = parseInt(input[1][28]);

export function part1() {
    let p1 = player1 - 1;
    let p1Points = 0;

    let p2 = player2 - 1;
    let p2Points = 0;

    let dice = 0;
    let rolls = 0;

    function roll() {
        let val = dice + 1;
        dice = val % 100;
        rolls++;
        return val;
    };
    function roll3() {
        return roll() + roll() + roll();
    };

    while (true) {
        p1 = (p1 + roll3()) % 10;
        p1Points += p1 + 1;
        if (p1Points >= 1000) break;

        p2 = (p2 + roll3()) % 10;
        p2Points += p2 + 1;
        if (p2Points >= 1000) break;
    }

    return Math.min(p1Points, p2Points) * rolls;
}


export function part2() {
    const rolls = [[3, 1], [4, 3], [5, 6], [6, 7], [7, 6], [8, 3], [9, 1]];

    let s0 = {
        p1: {
            position: player1 - 1,
            points: 0
        },
        p2: {
            position: player2 - 1,
            points: 0
        },
        turn: false,
        count: 1
    };

    let stack = [s0];

    let p1Win = 0;
    let p2Win = 0;
    while (stack.length > 0) {
        const el = stack.pop();

        for (const [roll, count] of rolls) {
            let next = {
                p1: { position: el.p1.position, points: el.p1.points },
                p2: { position: el.p2.position, points: el.p2.points },
                turn: !el.turn,
                count: el.count * count
            };

            if (!el.turn) {
                next.p1.position = (next.p1.position + roll) % 10;
                next.p1.points += next.p1.position + 1;
                if (next.p1.points >= 21) {
                    p1Win += next.count;
                } else stack.push(next);
            } else {
                next.p2.position = (next.p2.position + roll) % 10;
                next.p2.points += next.p2.position + 1;
                if (next.p2.points >= 21) {
                    p2Win += next.count;
                } else stack.push(next);
            }
        }
    }

    return Math.max(p1Win, p2Win);
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 576600);
    console.assert(part2() == 131888061854776);
}
