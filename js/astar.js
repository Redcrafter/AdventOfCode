
// manhattan http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
function heuristic(pos0, pos1) {
    let d1 = Math.abs(pos1.x - pos0.x);
    let d2 = Math.abs(pos1.y - pos0.y);
    return d1 + d2;
}

// https://github.com/bgrins/javascript-astar/blob/master/astar.js
/**
* Perform an A* Search on a graph given a start and end node.
* @param {Graph} graph
* @param {GridNode} start
* @param {GridNode} end
*/
export function astar(graph, start, end) {
    let openHeap = new BinaryHeap();

    start.h = heuristic(start, end);
    openHeap.push(start);

    while (openHeap.size() > 0) {
        // Grab the lowest f(x) to process next.  Heap keeps this sorted for us.
        let currentNode = openHeap.pop();

        // End case -- result has been found, return the traced path.
        if (currentNode === end) {
            return currentNode;
        }

        // Normal case -- move currentNode from open to closed, process each of its neighbors.
        currentNode.closed = true;

        // Find all neighbors for the current node.
        // let neighbors = graph.neighbors(currentNode);

        function func(neighbor) {
            if (neighbor.closed) {
                // Not a valid node to process, skip to next neighbor.
                return;
            }

            // The g score is the shortest distance from start to current node.
            // We need to check if the path we have arrived at this neighbor is the shortest one we have seen yet.
            let gScore = currentNode.g + neighbor.getCost(currentNode);
            let beenVisited = neighbor.visited;

            if (!beenVisited || gScore < neighbor.g) {

                // Found an optimal (so far) path to this node.  Take score for node to see how good it is.
                neighbor.visited = true;
                neighbor.parent = currentNode;
                neighbor.h = neighbor.h || heuristic(neighbor, end);
                neighbor.g = gScore;
                neighbor.f = neighbor.g + neighbor.h;

                if (!beenVisited) {
                    // Pushing to heap will put it in proper place based on the 'f' value.
                    openHeap.push(neighbor);
                } else {
                    // Already seen the node, but since it has been rescored we need to reorder it in the heap
                    openHeap.rescoreElement(neighbor);
                }
            }
        }

        let x = currentNode.x;
        let y = currentNode.y;
        let grid = graph.grid;

        if (x > 0) func(grid[x - 1][y]);
        if (x + 1 < grid[0].length) func(grid[x + 1][y]);
        if (y > 0) func(grid[x][y - 1]);
        if (y + 1 < grid.length) func(grid[x][y + 1]);
    }

    // No result was found - empty array signifies failure to find path.
    return null;
}

export class Graph {
    /**
     * A graph memory structure
     * @param {number} width
     * @param {number} height
     */
    constructor(width, height, costFunc) {
        this.grid = [];
        for (let x = 0; x < width; x++) {
            this.grid[x] = [];

            for (let y = 0; y < height; y++) {
                this.grid[x][y] = new GridNode(x, y, costFunc);
            }
        }
    }
}

class GridNode {
    constructor(x, y, costFunc) {
        this.x = x;
        this.y = y;

        this.f = 0;
        this.g = 0;
        this.h = 0;
        this.visited = false;
        this.closed = false;
        this.parent = null;

        this.costFunc = costFunc;
    }
    getCost() {
        return this.costFunc(this.x, this.y);
    }
}

export class BinaryHeap {
    constructor() {
        this.content = [];
    }

    push(element) {
        // Add the new element to the end of the array.
        this.content.push(element);

        // Allow it to sink down.
        this.sinkDown(this.content.length - 1);
    }

    pop() {
        // Store the first element so we can return it later.
        let result = this.content[0];
        // Get the element at the end of the array.
        let end = this.content.pop();
        // If there are any elements left, put the end element at the
        // start, and let it bubble up.
        if (this.content.length > 0) {
            this.content[0] = end;
            this.bubbleUp(0);
        }
        return result;
    }

    remove(node) {
        let i = this.content.indexOf(node);

        // When it is found, the process seen in 'pop' is repeated
        // to fill up the hole.
        let end = this.content.pop();

        if (i !== this.content.length - 1) {
            this.content[i] = end;

            if (end.f < node.f) {
                this.sinkDown(i);
            } else {
                this.bubbleUp(i);
            }
        }
    }

    size() {
        return this.content.length;
    }

    rescoreElement(node) {
        this.sinkDown(this.content.indexOf(node));
    }

    sinkDown(n) {
        // Fetch the element that has to be sunk.
        let element = this.content[n];

        // When at 0, an element can not sink any further.
        while (n > 0) {

            // Compute the parent element's index, and fetch it.
            let parentN = ((n + 1) >> 1) - 1;
            let parent = this.content[parentN];
            // Swap the elements if the parent is greater.
            if (element.f < parent.f) {
                this.content[parentN] = element;
                this.content[n] = parent;
                // Update 'n' to continue at the new position.
                n = parentN;
            } else {
                // Found a parent that is less, no need to sink any further.
                break;
            }
        }
    }

    bubbleUp(n) {
        // Look up the target element and its score.
        let length = this.content.length;
        let element = this.content[n];
        let elemScore = element.f;

        while (true) {
            // Compute the indices of the child elements.
            let child2N = (n + 1) << 1;
            let child1N = child2N - 1;
            // This is used to store the new position of the element, if any.
            let swap = null;
            let child1Score;
            // If the first child exists (is inside the array)...
            if (child1N < length) {
                // Look it up and compute its score.
                let child1 = this.content[child1N];
                child1Score = child1.f;

                // If the score is less than our element's, we need to swap.
                if (child1Score < elemScore) {
                    swap = child1N;
                }
            }

            // Do the same checks for the other child.
            if (child2N < length) {
                let child2 = this.content[child2N];
                let child2Score = child2.f;
                if (child2Score < (swap === null ? elemScore : child1Score)) {
                    swap = child2N;
                }
            }

            // If the element needs to be moved, swap it, and continue.
            if (swap !== null) {
                this.content[n] = this.content[swap];
                this.content[swap] = element;
                n = swap;
            } else {
                // Otherwise, we are done.
                break;
            }
        }
    }
};
