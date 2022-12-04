/**
 * @param {number} day 
 * @param {number} part 
 * @param {() => void} func 
 */
function runTest(func) {
    // force v8 to optimize functions
    let start = performance.now();
    for (let i = 0; i < 1000 && (performance.now() - start) < 10000; i++) {
        func();
    }

    let i = 0;
    let time = 0;
    while (i < 100000 && time < 10000) { // time < 2000
        let start = performance.now();
        func();
        let end = performance.now();

        time += end - start;
        i++;
    }
    time /= i;

    return (time * 1000).toFixed(4).padStart(10, " ") + "μs";
}

async function doDay(year, day) {
    let mod = await import(`./${year}/day-${day}.js`);

    let p1 = runTest(mod.part1);
    console.log(`${year}-${day.toString().padStart(2)}-${1} took ${p1}`);

    let p2 = runTest(mod.part2);
    console.log(`${year}-${day.toString().padStart(2)}-${2} took ${p2}`);

    return [p1, p2];
}

let table = [];
for (const year of [2020, 2021, 2022]) {
    for (let i = 1; i <= 25; i++) {
        try {
            let res = await doDay(year, i);
            table.push({ year, day: i, part1: res[0], part2: res[1] });
        } catch (e) { }
    }
}

console.table(table);
