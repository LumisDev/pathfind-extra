const pathfinder = require('./build/Release/pathfind-extra')
module.exports = {
    astar: (grid, start, goal) => {
        pathfinder.astar(grid, start, goal)
    }
}