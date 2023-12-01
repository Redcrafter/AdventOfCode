import fs from "fs";
import { fileURLToPath } from 'url';

/** @returns {NodeJS.CallSite[]} */
export function getCallStack() {
    let originalFunc = Error.prepareStackTrace;

    let stack = [];
    try {
        let err = new Error();
        Error.prepareStackTrace = function (err, stack) { return stack; };
        stack = err.stack;
    } catch (e) { }
    Error.prepareStackTrace = originalFunc;

    stack.shift();
    return stack;
}

export function _getCallerFile() {
    let stack = getCallStack();

    let currentfile = stack.shift().getFileName();
    let callerfile;
    while (stack.length) {
        callerfile = stack.shift().getFileName();
        if (currentfile !== callerfile) break;
    }

    return fileURLToPath(callerfile);
}

/**
 * @param {string} path 
 * @param {bool} skipEmpty 
 * @returns 
 */
export function readLines(path, skipEmpty = true) {
    let lines = fs.readFileSync(path).toString().split("\n");
    if (skipEmpty) lines = lines.filter(x => x.length != 0);
    return lines;
}

/**
 * @template T
 * @param {T[]} array 
 * @param {number|(T) => bool} size
 * @returns {T[][]}
 */
export function arraySplit(array, size) {
    let sections = [];
    let current = [];

    if (typeof size == "number") {
        for (let i = 0; i < array.length; i += size) {
            sections.push(array.slice(i, i + size));
        }
    } else {
        for (const item of array) {
            if (size(item)) {
                sections.push(current);
                current = [];
            } else {
                current.push(item);
            }
        }
        sections.push(current);
    }

    return sections;
}

export function getInput(skipEmpty = true) {
    let test = _getCallerFile().match(/\d+/g);

    let year = test.at(-2);
    let day = test.at(-1);

    let path = `./data/${year}/day${day}.txt`;

    return readLines(path, skipEmpty);
}

/**
 * @param {ArrayLike<number>} arr 
 * @returns 
 */
export function sum(arr) {
    let res = 0;
    for (let i = 0; i < arr.length; i++) {
        res += arr[i];
    }
    return res;
}

/**
 * [0, 0], [1, 1] => [[0, 1], [0, 1]]
 * @param  {...any[]} arrays 
 */
export function zip(...arrays) {
    let res = [];
    let len = Math.max(...arrays.map(x => x.length));
    for (let i = 0; i < len; i++) {
        res.push(arrays.map(x => x[i]));
    }
    return res;
}

export function extractNumbers(dat, readNegative = true) {
    if (Array.isArray(dat))
        return dat.map(x => extractNumbers(x, readNegative));

    if (readNegative) {
        return dat.match(/-?\d+/g)?.map(Number);
    } else {
        return dat.match(/\d+/g)?.map(Number);
    }
}

/**
 * @template {T}
 * @param {T[]} arr 
 * @param {number} size 
 * @returns {T[][]}
 */
export function window(arr, size) {
    let res = []
    for (let i = size; i < arr.length; i++) {
        res.push(arr.slice(i - size, i));
    }
    return res;
}

/**
 * fairly fast int parsing with support for negative numbers
 * @param {string} str 
 * @param {number} start 
 * @returns {number}
 */
export function parseInt(str, start = 0) {
    let val = 0;
    let neg = 1;
    if (str.charCodeAt(start) == 45) {
        start++;
        neg = -1;
    }

    for (let i = start; i < str.length; i++) {
        const c = str.charCodeAt(i);
        if (c < 48 || c > 57) break;

        val = val * 10 + c - 48
    }
    return val * neg;
}
