import { extractNumbers, getInput } from "../util.js";

const input = extractNumbers(getInput()).map(x => x[0]);
const h = input.length / 2;

const jumpSize = 20;

function buildList(mul) {
    let ll = [];

    let zero = null;
    let last = null;

    for (const item of input) {
        let el = {
            val: item * mul,
            prev: last,
            next: null,
            prevLong: null,
            nextLong: null,
        }
        if (last) last.next = el;
        last = el;
        ll.push(el);

        if (item == 0) zero = el;
    }
    ll[0].prev = last;
    last.next = ll[0];

    let a = ll[0];
    let b = ll[jumpSize];
    for (let i = 0; i < ll.length; i++) {
        a.nextLong = b;
        b.prevLong = a;

        a = a.next;
        b = b.next;
    }

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

        {
            let a = el.prevLong;
            let b = el.next;

            for (let i = 0; i < jumpSize; i++) {
                a.nextLong = b;
                b.prevLong = a;
                
                a = a.next;
                b = b.next;
            }
        }

        let a = el;
        if (move < 0) {
            while (move <= -jumpSize) {
                a = a.prevLong;
                move += jumpSize;
            }
            while (move < 0) {
                a = a.prev;
                move++
            }
            a = a.prev;
        } else if (move > 0) {
            while (move >= jumpSize) {
                a = a.nextLong;
                move -= jumpSize;
            }
            while (move > 0) {
                a = a.next;
                move--;
            }
        }
        let b = a.next;

        a.next = el;
        el.prev = a;

        el.next = b;
        b.prev = el;

        {
            let a1 = b.prevLong;
            let b1 = el;

            for (let i = 0; i < jumpSize + 1; i++) {
                a1.nextLong = b1;
                b1.prevLong = a1;
                
                a1 = a1.next;
                b1 = b1.next;
            }
        }
    }
}

function getAns(zero) {
    let a = zero;
    for (let i = 0; i < 50; i++) {
        a = a.nextLong;
    }
    let b = a;
    for (let i = 0; i < 50; i++) {
        b = b.nextLong;
    }
    let c = b;
    for (let i = 0; i < 50; i++) {
        c = c.nextLong;
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

import { checkAnswers } from "../test.js";
checkAnswers();
