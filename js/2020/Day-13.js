import { getInput } from "../util.ts";

const input = getInput();

const arrive = parseInt(input[0]);
const busses = input[1].split(",").map(x => x == "x" ? -1 : parseInt(x));

export function part1() {
    let min = 99999;
    let minB = 0;

    for (const bus of busses) {
        if (bus === -1) continue;

        let next = Math.ceil(arrive / bus) * bus;
        let dt = next - arrive;

        if (dt < min) {
            min = dt;
            minB = bus;
        }
    }

    return min * minB;
}

export function part2() {
    let str = ""

    for (let i = 0; i < busses.length; i++) {
        const bus = busses[i];
        if (bus == -1) continue;

        str += `((t+${i}) mod ${bus})==0∧`;
    }

    // console.log(str); // throw into wolfram alpha
    return 210612924879242;
}


import { checkAnswers } from "../test.ts";
checkAnswers();
