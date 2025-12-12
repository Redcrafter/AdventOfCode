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

export function readLines(path: string, skipEmpty = true): string[] {
    let lines = (fs.readFileSync(path) as string).toString().replaceAll("\r\n", "\n").split("\n");
    if (skipEmpty) lines = lines.filter(x => x.length != 0);
    return lines;
}

/**
 * splits array into chunks of size or based on predicate
 */
export function arraySplit<T>(array: T[], size: number | ((t: T) => boolean)) {
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

export function sum(arr: Iterable<number>): number {
    let res = 0;
    if (Array.isArray(arr)) {
        for (let i = 0; i < arr.length; i++) {
            res += arr[i];
        }
    } else {
        for (const val of arr) {
            res += val;
        }
    }
    return res;
}

export function zip<T>(...arrays: T[][]) {
    const res = [];
    const len = Math.max(...arrays.map(x => x.length));
    for (let i = 0; i < len; i++) {
        res.push(arrays.map(x => x[i]));
    }
    return res;
}

type ValueOrArray<T> = T | Array<ValueOrArray<T>>;
type Numberized<T> = T extends string ? number : T extends Array<infer U> ? Array<Numberized<U>> : never;

export function extractNumbers<T extends ValueOrArray<string>>(dat: T, readNegative = true): Numberized<T>[] {
    if (Array.isArray(dat))
        return dat.map(x => extractNumbers(x, readNegative));

    if (readNegative) {
        return dat.match(/-?\d+/g)?.map(Number) as number[];
    } else {
        return dat.match(/\d+/g)?.map(Number) as number[];
    }
}

export function window<T>(arr: T[], size: number, step = 1) {
    const res = []
    for (let i = size; i < arr.length; i += step) {
        res.push(arr.slice(i - size, i));
    }
    return res;
}

/**
 * fairly fast int parsing with support for negative numbers
 */
export function parseInt(str: string, start = 0) {
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
 */
export function radixSortUint32(input: number[]) {
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

export function bfs(walls: string[], x: number, y: number) {
    const height = walls.length;
    const width = walls[0].length;

    const grid = new Uint32Array(width * height);
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            grid[x + y * width] = -1;
        }
    }

    const stack = [];
    stack.push([x, y, 0]);

    function add(x: number, y: number, dist: number) {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return

        if (!grid[x + y * width]) {
            grid[x + y * width] = dist;
            stack.push([x, y, dist]);
        }
    }

    while (stack.length != 0) {
        const [x, y, dist] = stack.shift()!;

        add(x - 1, y, dist + 1);
        add(x + 1, y, dist + 1);
        add(x, y - 1, dist + 1);
        add(x, y + 1, dist + 1);
    }

    function backtrack(x: number, y: number, res: number[][]) {
        const d = grid[x + y * width];
        res.push([x, y]);
        if (d == 0) return;

        if (x > 0 && grid[(x - 1) + y * width] + 1 == d) backtrack(x - 1, y, res);
        if (x + 1 < width && grid[(x + 1) + y * width] + 1 == d) backtrack(x + 1, y, res);
        if (y > 0 && grid[x + (y - 1) * width] + 1 == d) backtrack(x, y - 1, res);
        if (y + 1 < height && grid[x + (y + 1) * width] + 1 == d) backtrack(x, y + 2, res);
    }

    return grid;
}
