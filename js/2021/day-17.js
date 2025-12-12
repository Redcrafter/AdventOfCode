import { getInput } from "../util.ts";

const _input = getInput()[0].match(/-?\d+/gm).map(x => parseInt(x));

let input = {
    left: _input[0],
    right: _input[1],
    bottom: _input[2],
    top: _input[3]
};

export function part1() {

    let globMax = 0;
    function fire(xVel, yVel) {
        let x = 0;
        let y = 0;

        let maxY = 0;

        while (x <= input.right && y >= input.bottom) {
            x += xVel;
            y += yVel;
            maxY = Math.max(maxY, y);

            if (x >= input.left && x <= input.right && y >= input.bottom && y <= input.top) {
                globMax = Math.max(maxY, globMax);
                break;
            }

            xVel -= Math.sign(xVel);
            yVel -= 1;
        }
    }

    for (let x = 23; x <= 100; x++) {
        for (let y = -100; y <= 100; y++) {
            fire(x, y);
        }
    }

    return globMax;
}

export function part2() {
    let hits = 0;
    function fire(xVel, yVel) {
        let x = 0;
        let y = 0;

        while (x <= input.right && y >= input.bottom) {
            x += xVel;
            y += yVel;

            if (x >= input.left && x <= input.right && y >= input.bottom && y <= input.top) {
                hits++;
                break;
            }

            xVel -= Math.sign(xVel);
            yVel -= 1;
        }
    }

    for (let x = 23; x <= input.right; x++) {
        for (let y = -100; y <= 1000; y++) {
            fire(x, y);
        }
    }

    return hits;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
