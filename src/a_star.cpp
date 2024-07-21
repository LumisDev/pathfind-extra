#include "a_star.h"
#include <cmath>
#include <algorithm>

float heuristic(const Node& a, const Node& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Node> get_neighbors(const Node& node, const std::vector<std::vector<int>>& grid) {
    std::vector<Node> neighbors;
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& dir : directions) {
        int nx = node.x + dir.first;
        int ny = node.y + dir.second;

        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 0) {
            neighbors.emplace_back(nx, ny);
        }
    }

    return neighbors;
}

std::vector<Node> reconstruct_path(Node* current) {
    std::vector<Node> path;
    while (current != nullptr) {
        path.push_back(*current);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node> astar(const std::vector<std::vector<int>>& grid, const Node& start, const Node& goal) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> open_set;
    std::unordered_set<Node, NodeHasher> closed_set;

    Node* start_node = new Node(start.x, start.y);
    Node* goal_node = new Node(goal.x, goal.y);

    open_set.push(start_node);

    while (!open_set.empty()) {
        Node* current = open_set.top();
        open_set.pop();

        if (*current == *goal_node) {
            return reconstruct_path(current);
        }

        closed_set.insert(*current);

        for (Node& neighbor : get_neighbors(*current, grid)) {
            if (closed_set.find(neighbor) != closed_set.end()) {
                continue;
            }

            float tentative_g = current->g + 1;

            if (tentative_g < neighbor.g || neighbor.g == 0) {
                neighbor.parent = current;
                neighbor.g = tentative_g;
                neighbor.h = heuristic(neighbor, *goal_node);
                neighbor.f = neighbor.g + neighbor.h;

                open_set.push(new Node(neighbor));
            }
        }
    }

    return {};
}
