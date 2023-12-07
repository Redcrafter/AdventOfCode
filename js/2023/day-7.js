import { getInput } from "../util.js";

const input = getInput();

export function part1() {
    const rating = "AKQJT98765432";
    function comp(a, b) {
        return rating.indexOf(b) - rating.indexOf(a);
    }

    function getType(hand) {
        let m = new Map();

        for (let i = 0; i < hand.length; i++) {
            const item = hand[i];

            m.set(item, (m.get(item) ?? 0) + 1);
        }

        let raw = [...m];
        if (m.size == 1) { // Five of a kind
            return 6;
        } else if (m.size == 2) {
            if (raw.some(x => x[1] == 4)) { // Four of a kind
                return 5;
            } else { // Full house
                return 4;
            }
        } else if (m.size == 3) {
            if (raw.some(x => x[1] == 3)) { // Three of a kind
                return 3;
            } else { // Two pair
                return 2;
            }
        } else if (m.size == 4) { // One pair
            return 1;
        } else { // High card
            return 0;
        }
    }
    let cards = [];
    for (const line of input) {
        let hand = line.substring(0, 5);
        let bet = parseInt(line.substring(6));

        let type = getType(hand);
        cards.push({ hand, bet, type })
    }

    cards.sort((a, b) => {
        return a.type - b.type ||
            comp(a.hand[0], b.hand[0]) ||
            comp(a.hand[1], b.hand[1]) ||
            comp(a.hand[2], b.hand[2]) ||
            comp(a.hand[3], b.hand[3]) ||
            comp(a.hand[4], b.hand[4]);
    });

    let result = 0;

    for (let i = 0; i < cards.length; i++) {
        const c = cards[i];
        result += (i + 1) * c.bet;
    }

    return result;
}

export function part2() {
    const rating = "AKQT98765432J";

    function comp(a, b) {
        return rating.indexOf(b) - rating.indexOf(a);
    }

    function getType(hand) {
        let m = new Map();

        for (let i = 0; i < hand.length; i++) {
            const item = hand[i];

            m.set(item, (m.get(item) ?? 0) + 1);
        }

        let raw = [...m];
        if (m.size == 1) { // Five of a kind
            return 6;
        } else if (m.size == 2) {
            if (m.has("J"))
                return 6;
            if (raw.some(x => x[1] == 4)) { // Four of a kind
                return 5;
            } else { // Full house
                return 4;
            }
        } else if (m.size == 3) {
            if (raw.some(x => x[1] == 3)) { // Three of a kind
                if (m.has("J"))
                    return 5;
                return 3;
            } else { // Two pair
                if (m.get("J") == 1)
                    return 4;
                if (m.get("J") == 2)
                    return 5;
                return 2;
            }
        } else if (m.size == 4) { // One pair
            if (m.has("J"))
                return 3;
            return 1;
        } else { // High card
            if (m.has("J"))
                return 1;
            return 0;
        }
    }
    let cards = [];
    for (const line of input) {
        let hand = line.substring(0, 5);
        let bet = parseInt(line.substring(6));

        let type = getType(hand);
        cards.push({ hand, bet, type })
    }

    cards.sort((a, b) => {
        return a.type - b.type ||
            comp(a.hand[0], b.hand[0]) ||
            comp(a.hand[1], b.hand[1]) ||
            comp(a.hand[2], b.hand[2]) ||
            comp(a.hand[3], b.hand[3]) ||
            comp(a.hand[4], b.hand[4]);
    });

    let result = 0;

    for (let i = 0; i < cards.length; i++) {
        const c = cards[i];
        result += (i + 1) * c.bet;
    }

    return result;
}

import { checkAnswers } from "../test.js";
checkAnswers();
