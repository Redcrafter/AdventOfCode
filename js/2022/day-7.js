import { getInput, window } from "../util.js";
const input = getInput();

function calcTree() {
    function makeNode(parent) {
        return { parent, ownSize: 0, children: [], s: 0 };
    }
    let root = makeNode(null);
    let current = root;

    for (let i = 0; i < input.length;) {
        let line = input[i];
        i++;

        if (line[2] == "c") {
            if (line[5] == "/") {
                current = root;
            } else if (line[5] == ".") {
                current.parent.s += current.s;
                current = current.parent;
            } else {
                let c = makeNode(current);
                current.children.push(c);
                current = c;
            }
        } else {
            let size = 0;
            while (i < input.length && input[i][0] != "$") {
                if(input[i][0] != "d") {
                    size += parseInt(input[i]);
                }
                i++;
            }
            current.ownSize = size;
            current.s += size;
        }
    }

    return root;
}

export function part1() {
    let root = calcTree();

    let res = 0;

    function calcSize(node) {
        if (node.s < 100000) res += node.s;
        for (const c of node.children) {
            calcSize(c);
        }
    }
    calcSize(root);

    return res;
}

export function part2() {
    let root = calcTree();

    let req = 30000000 - (70000000 - root.s);
    let m = Infinity;

    function calcMin(node) {
        if (node.s < req) return;
        if (node.s < m) m = node.s;
        for (const c of node.children) {
            calcMin(c)
        }
    }
    calcMin(root);
    return m;
}

import { fileURLToPath } from 'url';
if (process.argv[1] === fileURLToPath(import.meta.url)) {
    console.assert(part1() == 1667443);
    console.assert(part2() == 8998590);
}
