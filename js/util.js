import fs from "fs";

/** @returns {NodeJS.CallSite[]} */
export function getCallStack() {
    const originalFunc = Error.prepareStackTrace;

    let stack = [];
    try {
        const err = new Error();
        Error.prepareStackTrace = function (_, stack) { return stack; };
        stack = err.stack;
    } catch { }
    Error.prepareStackTrace = originalFunc;

    stack.shift();
    return stack;
}

export function _getCallerFile() {
    const stack = getCallStack();

    const currentfile = stack.shift().getFileName();
    let callerfile;
    while (stack.length) {
        callerfile = stack.shift().getFileName();
        if (currentfile !== callerfile) break;
    }

    return callerfile;
}

/**
 * @param {string} path 
 * @param {bool} skipEmpty 
 * @returns {string[]}
 */
export function readLines(path, skipEmpty = true) {
    let lines = fs.readFileSync(path).toString().split("\n");
    if (skipEmpty) lines = lines.filter(x => x.length != 0);
    return lines;
}

/**
 * splits array into chunks of size or based on predicate
 * @template T
 * @param {T[]} array 
 * @param {number|(T) => bool} size
 * @returns {T[][]}
 */
export function arraySplit(array, size) {
    const sections = [];
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
    const test = _getCallerFile().match(/\d+/g);

    const year = test.at(-2);
    const day = test.at(-1);

    const path = `./data/${year}/day${day}.txt`;

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
    const res = [];
    const len = Math.max(...arrays.map(x => x.length));
    for (let i = 0; i < len; i++) {
        res.push(arrays.map(x => x[i]));
    }
    return res;
}

/**
 * 
 * @param {string|string[]} dat 
 * @param {boolean} readNegative 
 * @returns {number[][]}
 */
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
export function window(arr, size, step = 1) {
    const res = []
    for (let i = size; i < arr.length; i += step) {
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

/**
 * see https://stackoverflow.com/a/46720474
 * @param {ArrayLike<number>} input
 */
export function radixSortUint32(input) {
    const arrayConstr = input.length < (1 << 16) ? Uint16Array : Uint32Array;
    const numberOfBins = 256 * 4;
    const count = new arrayConstr(numberOfBins);

    const output = new Uint32Array(input.length);

    // count all bytes in one pass
    for (let i = 0; i < input.length; i++) {
        const val = input[i];
        count[val & 0xFF]++;
        count[((val >> 8) & 0xFF) | 256]++;
        count[((val >> 16) & 0xFF) | 512]++;
        count[((val >> 24) & 0xFF) | 768]++;
    }

    // create summed array
    for (let j = 0; j < 4; j++) {
        let t = 0;
        let sum = 0;
        const offset = j * 256;
        for (let i = 0; i < 256; i++) {
            t = count[i + offset];
            count[i + offset] = sum;
            sum += t;
        }
    }

    for (let i = 0; i < input.length; i++) {
        const val = input[i];
        output[count[val & 0xFF]++] = val;
    }
    for (let i = 0; i < input.length; i++) {
        const val = output[i];
        input[count[((val >> 8) & 0xFF) | 256]++] = val;
    }
    for (let i = 0; i < input.length; i++) {
        const val = input[i];
        output[count[((val >> 16) & 0xFF) | 512]++] = val;
    }
    for (let i = 0; i < input.length; i++) {
        const val = output[i];
        input[count[((val >> 24) & 0xFF) | 768]++] = val;
    }

    return input;
}
