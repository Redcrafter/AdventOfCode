import { getInput } from "../util.ts";

const input = getInput();

function isSymbol(c) {
    return c == "*" ||
        c == "@" ||
        c == "-" ||
        c == "+" ||
        c == "#" ||
        c == "%" ||
        c == "=" ||
        c == "/" ||
        c == "$" ||
        c == "&";
}

function isDigit(c) {
    let a = c?.charCodeAt(0);
    return a >= 48 && a <= 57;
}

function checkEdge(x, y, len) {
    for (let x1 = -1; x1 <= len; x1++) {
        if (isSymbol(input[y - 1]?.[x + x1]))
            return true;
        if (isSymbol(input[y + 1]?.[x + x1]))
            return true;
    }

    if (isSymbol(input[y][x - 1]))
        return true;
    if (isSymbol(input[y][x + len]))
        return true;

    return false;
}

export function part1() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        let j = 0;
        while (j < line.length) {
            let c = line.charCodeAt(j);

            if (c >= 48 && c <= 57) {
                let num = 0;
                let len = 0;
                while (c >= 48 && c <= 57) {
                    num = num * 10 + c - 48;
                    c = line.charCodeAt(j + ++len);
                }

                if (checkEdge(j, i, len)) {
                    result += num;
                }

                j += len;
            } else {
                j++;
            }
        }
    }

    return result;
}

export function part2() {
    let result = 0;

    for (let i = 0; i < input.length; i++) {
        const line = input[i];

        for (let j = 0; j < line.length; j++) {
            if (line[j] !== "*")
                continue;

            let n1 = 0;
            let n2 = 0;
            
            if (i > 0) {
                for (let x = -1; x <= 1;) {
                    if (isDigit(input[i - 1][j + x])) {
                        // find start
                        let s = j + x;
                        while (isDigit(input[i - 1][s - 1])) {
                            s--;
                        }
                        let e = j + x;
                        while (isDigit(input[i - 1][e])) {
                            e++;
                        }
                        let v = input[i - 1].substring(s, e);
                        if (n1) n2 = parseInt(v);
                        else n1 = parseInt(v);
                        x = e - j;
                    } else {
                        x++;
                    }
                }
            }

            for (let x = -1; x <= 1;) {
                if (isDigit(input[i][j + x])) {
                    // find start
                    let s = j + x;
                    while (isDigit(input[i][s - 1])) {
                        s--;
                    }
                    let e = j + x;
                    while (isDigit(input[i][e])) {
                        e++;
                    }
                    let v = input[i].substring(s, e);
                    if (n1) n2 = parseInt(v);
                    else n1 = parseInt(v);
                    x = e - j;
                } else {
                    x++;
                }
            }

            if (i + 1 < input.length) {
                for (let x = -1; x <= 1;) {
                    if (isDigit(input[i + 1][j + x])) {
                        // find start
                        let s = j + x;
                        while (isDigit(input[i + 1][s - 1])) {
                            s--;
                        }
                        let e = j + x;
                        while (isDigit(input[i + 1][e])) {
                            e++;
                        }
                        let v = input[i + 1].substring(s, e);
                        if (n1) n2 = parseInt(v);
                        else n1 = parseInt(v);
                        x = e - j;
                    } else {
                        x++;
                    }
                }
            }

            result += n1 * n2;
        }
    }

    return result;
}

import { checkAnswers } from "../test.ts";
checkAnswers();
