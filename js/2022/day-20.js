import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput()).map(x => x[0]);
const h = input.length / 2;

function buildList(mul) {
    let ll = [];

    let zero = null;
    let last = null;

    for (const item of input) {
        let el = {
            val: item * mul,
            prev: last,
            next: null
        }
        if (last) last.next = el;
        last = el;
        ll.push(el);

        if (item == 0) zero = el;
    }
    ll[0].prev = last;
    last.next = ll[0];

    return [ll, zero];
}

function doLoop(ll) {
    for (const el of ll) {
        let move = el.val % (input.length - 1);
        if (move == 0) continue;

        if (move > h) move -= (input.length - 1);
        if (move < -h) move += (input.length - 1);

        el.prev.next = el.next;
        el.next.prev = el.prev;

        let a = el;
        if (move < 0) {
            for (let i = move; i < 0; i++) {
                a = a.prev;
            }
            a = a.prev;
        } else if (move > 0) {
            for (let i = 0; i < move; i++) {
                a = a.next;
            }
        }
        let b = a.next;

        a.next = el;
        el.prev = a;

        el.next = b;
        b.prev = el;
    }
}

function getAns(zero) {
    let a = zero;
    for (let i = 0; i < 1000; i++) {
        a = a.next;
    }
    let b = a;
    for (let i = 0; i < 1000; i++) {
        b = b.next;
    }
    let c = b;
    for (let i = 0; i < 1000; i++) {
        c = c.next;
    }
    return a.val + b.val + c.val;
}

export function part1() {
    const [ll, zero] = buildList(1);
    doLoop(ll);
    return getAns(zero);
}

export function part2() {
    const [ll, zero] = buildList(811589153);

    for (let i = 0; i < 10; i++) {
        doLoop(ll);
    }

    return getAns(zero);
}

import { checkAnsweres } from "../test.js";
checkAnsweres();
