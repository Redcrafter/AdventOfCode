import { getInput } from "../util.js";
const input = getInput(false);

let ports = [];
let temp = [];
for (const l of input) {
    if (l == "") {
        ports.push(new Map(temp.map(x => x.split(":"))));
        temp = [];
    } else {
        temp.push(...l.split(" "));
    }
}

export function part1() {
    let present = 0;

    for (const p of ports) {
        if (!["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"].every(x => p.has(x))) continue;

        present++;
    }

    return present;
}
export function part2() {
    let valid = 0;

    for (const p of ports) {
        if (!["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"].every(x => p.has(x))) continue;

        let hgt = p.get("hgt");
        let hgtVal = parseInt(hgt);
        if (!((hgt.endsWith("cm") && hgtVal >= 150 && hgtVal <= 193) || (hgt.endsWith("in") && hgtVal >= 59 && hgtVal <= 76)) ||
            p.get("byr") < 1920 || p.get("byr") > 2002 ||
            p.get("iyr") < 2010 || p.get("iyr") > 2020 ||
            p.get("eyr") < 2020 || p.get("eyr") > 2030 ||
            !p.get("hcl").match(/^#[0-9a-f]{6}$/) ||
            !p.get("ecl").match(/^(amb|blu|brn|gry|grn|hzl|oth)$/) ||
            !p.get("pid").match(/^[0-9]{9}$/)) continue;

        valid++;
    }

    return valid;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 230)
    console.assert(part2() == 156)
}
