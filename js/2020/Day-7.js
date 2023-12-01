import { getInput } from "../util.js";
const input = getInput().map(l => {
    let arr = l.split(/ bags contain |, /);

    let name = arr[0];
    let res;
    if (arr[1] == "no other bags.") res = []
    else res = arr.slice(1).map(x => {
        let test = x.match(/(\d+) (\w+ \w+) /);
        return [parseInt(test[1]), test[2]];
    });

    return [name, res];
});

export function part1() {
    let map = new Map();

    for (const item of input) {
        for (const [count, name] of item[1]) {

            if (map.has(name)) {
                map.get(name).push(item[0]);
            } else {
                map.set(name, [item[0]])
            }
        }
    }

    let set = new Set();

    let stack = ["shiny gold"];
    while (stack.length) {
        let el = stack.pop();
        set.add(el);

        let r = map.get(el);
        if (!r) continue;

        for (const item of r) {
            if (!set.has(item))
                stack.push(item);
        }
    }
    return set.size - 1;
}

export function part2() {
    const m = new Map(input);

    function countBags(name) {
        let count = 1;
        for (const item of m.get(name)) {
            count += countBags(item[1]) * item[0];
        }
        return count;
    }

    return countBags("shiny gold") - 1;
}

import { checkAnswers } from "../test.js";
checkAnswers();
