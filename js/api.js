import fs from "fs";

const session = "";

if (session.length == 0) {
    console.log("Missing session token. Please set in 'js/api.js'");
    process.exit();
}

export async function downloadInput(year, day) {
    const path = `./data/${year}/day${day}.txt`;
    if (fs.existsSync(path)) return;

    const req = await fetch(`https://adventofcode.com/${year}/day/${day}/input`, {
        headers: { Cookie: `session=${session}` }
    });
    if (req.ok) {
        let text = await req.text();
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
