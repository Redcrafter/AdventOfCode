
const warmUpTime = 1 * 1e9; // 1 second

const testTime = 30 * 1e9; // 30 seconds
const maxIters = 1_000_000;

function now() {
    return process.hrtime.bigint();
}

function format(n) {
    return (n / 1000).toFixed(1).padStart(7) + "μs";
}

/**
 * @param {number} day 
 * @param {number} part 
 * @param {() => void} func 
 */
function runTest(func) {
    // force v8 to optimize functions
    let start = now();
    while ((now() - start) < warmUpTime) {
        func();
    }

    let i = 0;
    let time = 0;
    let min = Infinity;
    let max = 0;
    let times = [];

    while (time < testTime && i < maxIters) {
        let start = now();
        func();
        let end = now();

        let dt = Number(end - start);
        times.push(dt);

        if (dt < min) min = dt;
        if (dt > max) max = dt;

        time += dt;
        i++;
    }

    return [min, max, time / i, times];
}

function median(arr) {
    let mid = arr.length / 2;
    if (arr.length % 2 == 0) {
        return (arr[mid] + arr[mid + 1]) / 2;
    } else {
        return arr[Math.floor(mid)];
    }
}

function drawGraph(times, mean) {
    const height = 5;
    let width = 100;

    times.sort((a, b) => a - b);

    let q2 = median(times);
    let q1 = median(times.slice(0, times.length / 2));
    let q3 = median(times.slice(times.length / 2));
    let iqr = q3 - q1;

    if (iqr < 100) iqr = 100;

    let upper = q3 + (1.5 * iqr);
    let lower = q1 - (1.5 * iqr);
    lower = Math.max(lower, times[0]);

    let range = upper - lower;

    let dist = new Uint32Array(width);
    let dMax = 0;

    let stdDiv = 0;

    for (const item of times) {
        stdDiv += (item - mean) ** 2;

        let pos = Math.floor(((item - lower) / range) * width);
        if (pos < 0 || pos >= width) continue;

        dist[pos]++;
        dMax = Math.max(dMax, dist[pos]);
    }

    // interpolate gaps if time resoultion is not high enough
    // doesn't work for 2 wide gaps
    for (let i = 1; i < dist.length - 1; i++) {
        if(dist[i] == 0) {
            dist[i] = (dist[i - 1] + dist[i + 1]) / 2;
        }
    }

    stdDiv = Math.sqrt(stdDiv / (times.length - 1));

    const blocks = " ▁▂▃▄▅▆▇█";
    let result = [];
    for (let i = 0; i < height; i++) {
        result.push(new Array(width).fill(" "));
    }

    for (let x = 0; x < dist.length; x++) {
        let h = (dist[x] / dMax) * height;

        let y = height - 1;
        while (h > 0) {
            result[y][x] = blocks[Math.min(8, Math.floor(h * 9))];
            y--;
            h--;
        }
    }

    console.log(`Range (min … max): ${format(times[0])} … ${format(times.at(-1))}`);
    console.log(`Time  (median):    ${format(q2)}`);
    console.log(`Time  (mean ± σ):  ${format(mean)} ± ${format(stdDiv)}`);
    console.log();

    for (let y = 0; y < height; y++) {
        process.stdout.write(result[y].join(""));
        process.stdout.write("\n");
    }

    if (q2 == lower) {
        q2 = lower + range / 2;
    }

    let mid = Math.floor(((q2 - lower) / range) * width) + 1;

    process.stdout.write("└");
    process.stdout.write("─".repeat(mid - 2));
    process.stdout.write("┴");
    process.stdout.write("─".repeat(width - mid - 1));
    process.stdout.write("┘\n");

    let l = (lower / 1000).toFixed(1) + "μs";
    let m = (q2 / 1000).toFixed(1) + "μs";
    let r = (upper / 1000).toFixed(1) + "μs"
    process.stdout.write(l);
    process.stdout.write(" ".repeat(Math.max(1, mid - l.length - m.length / 2)));
    process.stdout.write(m);
    process.stdout.write(" ".repeat(width - mid - m.length / 2 + 1 - r.length));
    process.stdout.write(r);
    process.stdout.write("\n\n");
}

async function doDay(year, day) {
    let mod = await import(`./${year}/day-${day}.js`);

    let p1 = runTest(mod.part1);
    console.log(`Year ${year} Day ${day} Part 1`);
    drawGraph(p1[3], p1[2]);

    let p2 = runTest(mod.part2);
    console.log(`Year ${year} Day ${day} Part 2`);
    drawGraph(p2[3], p2[2]);

    return [p1, p2];
}

let table = [];
for (const year of [2020, 2021, 2022, 2023]) {
    for (let i = 1; i <= 25; i++) {
        try {
            let res = await doDay(year, i);
            table.push({
                year,
                day: i,
                part: 1,
                min: format(res[0][0]),
                max: format(res[0][1]),
                avg: format(res[0][2]),
                med: format(median(res[0][3]))
            });
            table.push({
                year,
                day: i,
                part: 2,
                min: format(res[1][0]),
                max: format(res[1][1]),
                avg: format(res[1][2]),
                med: format(median(res[1][3]))
            });
        } catch (e) { }
    }
}

console.table(table);
