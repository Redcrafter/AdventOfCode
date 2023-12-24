import fs from "fs";
import readline from "readline";
import { fileURLToPath } from "url";

import { downloadInput } from "./api.js";
import { getCallStack, _getCallerFile } from "./util.js";

let testAll = false;

const red = "\x1b[31m";
const green = "\x1b[32m";
const reset = "\x1b[0m";

let solutions = null;
let results = {};
if (!fs.existsSync(`./data/solutions.json`)) {
    console.log(`${red}Missing solutions.json${reset}`);
} else {
    solutions = JSON.parse(fs.readFileSync(`./data/solutions.json`));
}

function format(pad, val) {
    if (val === null) {
        return "N/A";
    }
    val = val.toString().split("\n");

    for (let i = 1; i < val.length; i++) {
        val[i] = " ".repeat(pad) + val[i];
    }

    return val.join("\n");
}

export async function checkAnswers() {
    let stack = getCallStack();
    let callFile = stack[1].getFileName();

    // only check if day is run directly
    if (!testAll && process.argv[1] !== fileURLToPath(callFile)) {
        return;
    }

    let test = callFile.match(/\d+/g);
    let year = test.at(-2);
    let day = test.at(-1);

    let mod = await import(`./${year}/day-${day}.js`);

    if (!solutions) {
        let p1 = await mod.part1();
        let p2 = await mod.part2();
        console.log(`[${year}-${day.padStart(2)}-1] ${format(12, p1)}`);
        console.log(`[${year}-${day.padStart(2)}-2] ${format(12, p2)}`);

        let y = results[year];
        if (!y) y = results[year] = {};

        y[day] = [p1, p2];
        return;
    }

    let sol = solutions[year]?.[day];

    if (!sol) {
        console.log(`${red}Missing solutions for Year ${year} Day ${day} showing results:${reset}`);
        console.log(`Part 1: ${format(8, await mod.part1())}`);
        console.log(`Part 2: ${format(8, await mod.part2())}`);
        return;
    }

    let p1 = await mod.part1();
    if (p1 === sol[0]) {
        console.log(`${green}[${year}-${day}-1] Passed${reset}`);
    } else {
        console.log(`[${year}-${day}-1] Failed - Result: ${p1} - Expected: ${sol[0]}`);
    }

    let p2 = await mod.part2();
    if (p2 === sol[1]) {
        console.log(`${green}[${year}-${day}-2] Passed${reset}`);
    } else {
        console.log(`[${year}-${day}-2] Failed - Result: ${p2} - Expected: ${sol[1]}`);
    }
}

async function main() {
    testAll = true;

    for (const year of [2020, 2021, 2022]) {
        for (let i = 1; i <= 25; i++) {
            if (!fs.existsSync(`./js/${year}/day-${i}.js`))
                continue;
            await downloadInput(year, i);

            try {
                await import(`./${year}/day-${i}.js`);
            } catch (e) {
                console.log(e);
            }
        }
        console.log();
    }

    if (!solutions) {
        await new Promise(r => setTimeout(r, 1000)); // wait for last day to finish
        const inquirer = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        });

        inquirer.question("Save input to solutions.json? (Y/n)", val => {
            val = val.toLowerCase();
            if (val == "" || val == "y") {
                fs.writeFileSync("./data/solutions.json", JSON.stringify(results));
            }
            inquirer.close();
        });
    }
}

if (process.argv[1] === fileURLToPath(import.meta.url)) {
    main();
}
