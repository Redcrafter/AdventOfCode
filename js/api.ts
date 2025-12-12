import fs from "fs";
import process from "process";

const session = "53616c7465645f5fbc9d8c427ea002e38a05dc6143cf9cb4bb415e9fb76a6737184f35d0fb6099f236d05376e9a7bceba7d547c5c2f75361c4262172d24ba41f";

if (session.length == 0) {
    console.log("Missing session token. Please set in 'js/api.js'");
    process.exit();
}

export async function downloadInput(year: number, day: number) {
    const path = `./data/${year}/day${day}.txt`;
    if (fs.existsSync(path)) return;

    const req = await fetch(`https://adventofcode.com/${year}/day/${day}/input`, {
        headers: { Cookie: `session=${session}` }
    });
    if (req.ok) {
        const text = await req.text();
        fs.mkdirSync(`./data/${year}/`, { recursive: true });
        fs.writeFileSync(path, text);
    }
}

if (import.meta.main) {
    for (const year of [2020, 2021, 2022, 2023, 2024]) {
        for (let i = 1; i <= 25; i++) {
            await downloadInput(year, i);
        }
    }
}
