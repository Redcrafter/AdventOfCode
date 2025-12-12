import process from "process";

const warmUpTime = 1 * 1e9; // 1 second

const testTime = 10 * 1e9; // 10 seconds
const maxIters = 1_000_000;

function now(): bigint {
    return process.hrtime.bigint();
}

function format(n: number) {
    return (n / 1000).toFixed(1).padStart(7) + "μs";
}

// warms up v8 engine and estimates the function runtime
function warmUp_estimate<T>(func: () => T) {
    // force v8 to optimize functions
    const start = now();

    // exponentially increase number of estimation itterations
    for (let i = 0; ; i++) {
        const start1 = now();
        for (let j = 0; j < (1 << i); j++) {
            func();
        }
        const end = now();

        if ((end - start) >= warmUpTime) {
            return Number(end - start1) / (1 << i);
        }
    }
}

function runTest<T>(func: () => T) {
    const runs = Math.ceil(100_0000 / warmUp_estimate(func));

    let i = 0;
    let time = 0;
    let min = Infinity;
    let max = 0;
    const times = [];

    while (time < testTime && i < maxIters) {
        const start = now();
        for (let j = 0; j < runs; j++) {
            func();
        }
        const end = now();

        const dt = Number(end - start);
        times.push(dt / runs);

        if (dt < min) min = dt;
        if (dt > max) max = dt;

        time += dt;
        i += runs;
    }

    return { min, max, avg: time / i, times };
}

function median(arr: number[]) {
    const mid = arr.length / 2;
    if (arr.length % 2 == 0) {
        return (arr[mid] + arr[mid + 1]) / 2;
    } else {
        return arr[Math.floor(mid)];
    }
}

function stdDiv(times: number[], mean: number) {
    let stdDiv = 0;
    for (const item of times)
        stdDiv += (item - mean) ** 2;
    return Math.sqrt(stdDiv / (times.length - 1));
}

function drawGraph(times: number[], mean: number) {
    const height = 5;
    const width = 100;

    times.sort((a, b) => a - b);

    const σ = stdDiv(times, mean);

    let q2 = median(times);
    const q1 = median(times.slice(0, times.length / 2));
    const q3 = median(times.slice(times.length / 2));
    const iqr = Math.max(q3 - q1, 100);

    const upper = q3 + (1.5 * iqr);
    const lower = Math.max(q1 - (1.5 * iqr), times[0]);
    const range = upper - lower;

    const dist = new Float64Array(width);
    for (const item of times) {
        const pos = Math.floor(((item - lower) / range) * width);
        if (pos >= 0 || pos < width) dist[pos]++;
    }

    const blocks = " ▁▂▃▄▅▆▇█";
    const result = [];
    for (let i = 0; i < height; i++) {
        result.push(new Array(width).fill(" "));
    }

    const dMax = dist.reduce((v, x) => Math.max(v, x), 0);
    for (let x = 0; x < dist.length; x++) {
        let h = (dist[x] / dMax) * height;

        let y = height - 1;
        while (h > 0) {
            result[y][x] = blocks[Math.min(8, Math.floor(h * 9))];
            y--;
            h--;
        }
    }

    console.log(`Range (min … max): ${format(times[0])} … ${format(times.at(-1)!)}`);
    console.log(`Time  (median):    ${format(q2)}`);
    console.log(`Time  (mean ± σ):  ${format(mean)} ± ${format(σ)}`);
    console.log();

    for (let y = 0; y < height; y++) {
        process.stdout.write(result[y].join(""));
        process.stdout.write("\n");
    }

    if (q2 == lower) {
        q2 = lower + range / 2;
    }

    const mid = Math.floor(((q2 - lower) / range) * width) + 1;

    process.stdout.write("└");
    process.stdout.write("─".repeat(Math.max(mid - 2, 0)));
    process.stdout.write("┴");
    process.stdout.write("─".repeat(width - mid - 1));
    process.stdout.write("┘\n");

    const l = (lower / 1000).toFixed(1) + "μs";
    const m = (q2 / 1000).toFixed(1) + "μs";
    const r = (upper / 1000).toFixed(1) + "μs"
    process.stdout.write(l);
    process.stdout.write(" ".repeat(Math.max(1, mid - l.length - m.length / 2)));
    process.stdout.write(m);
    process.stdout.write(" ".repeat(width - mid - m.length / 2 + 1 - r.length));
    process.stdout.write(r);
    process.stdout.write("\n\n");
}

async function doDay(year: number, day: number) {
    const mod = await import(`./${year}/day-${day}.js`);

    const p1 = runTest(mod.part1);
    console.log(`Year ${year} Day ${day} Part 1`);
    drawGraph(p1.times, p1.avg);

    const p2 = runTest(mod.part2);
    console.log(`Year ${year} Day ${day} Part 2`);
    drawGraph(p2.times, p2.avg);

    return [p1, p2];
}

const table = [];
for (const year of [2020, 2021, 2022, 2023, 2024]) {
    for (let i = 1; i <= 25; i++) {
        try {
            const res = await doDay(year, i);
            table.push({
                year,
                day: i,
                part: 1,
                min: format(res[0].min),
                max: format(res[0].max),
                avg: format(res[0].avg),
                med: format(median(res[0].times))
            });
            table.push({
                year,
                day: i,
                part: 2,
                min: format(res[1].min),
                max: format(res[1].max),
                avg: format(res[1].avg),
                med: format(median(res[1].times))
            });
        } catch (e) { }
    }
}

console.table(table);
