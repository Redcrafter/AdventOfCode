
function now() {
    return process.hrtime.bigint();
}

function format(n) {
    return (Number(n) / 1000).toFixed(1).padStart(7, " ") + "μs";
}

/**
 * @param {number} day 
 * @param {number} part 
 * @param {() => void} func 
 */
function runTest(func) {
    // force v8 to optimize functions
    let start = now();
    for (let i = 0; i < 1000 && (now() - start) < 1_000_000_000; i++) {
        func();
    }

    let i = 0;
    let time = 0n;
    let min = 9999999999999n;
    let max = 0n;

    while (time < 10_000_000_000) {
        let start = now();
        func();
        let end = now();

        let dt = end - start;

        if (dt < min) min = dt;
        if (dt > max) max = dt;

        time += dt;
        i++;
    }

    return [min, max, time / BigInt(i)];
}

async function doDay(year, day) {
    let mod = await import(`./${year}/day-${day}.js`);

    let p1 = runTest(mod.part1);
    console.log(`${year} ${day.toString().padStart(2)}-${1} ${p1.map(format).join(" ")}`);

    let p2 = runTest(mod.part2);
    console.log(`${year} ${day.toString().padStart(2)}-${2} ${p2.map(format).join(" ")}`);

    return [p1, p2];
}

console.log("                min       max   average");

let table = [];
for (const year of [2022]) {
    for (let i = 1; i <= 25; i++) {
        try {
            let res = await doDay(year, i);
            table.push({
                year,
                day: i,
                part: 1,
                min: format(res[0][0]),
                max: format(res[0][1]),
                avg: format(res[0][2])
            });
            table.push({
                year,
                day: i,
                part: 2,
                min: format(res[1][0]),
                max: format(res[1][1]),
                avg: format(res[1][2])
            });
        } catch (e) { }
    }
}

console.table(table);
