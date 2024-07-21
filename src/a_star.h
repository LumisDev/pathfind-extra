#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <unordered_set>
#include <queue>

struct Node {
    int x, y;
    Node* parent;
    float g, h, f;

    Node(int x, int y, Node* parent = nullptr)
        : x(x), y(y), parent(parent), g(0), h(0), f(0) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

struct NodeHasher {
    size_t operator()(const Node& node) const {
        return std::hash<int>()(node.x) ^ std::hash<int>()(node.y);
    }
};

struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->f > rhs->f;
    }
};

float heuristic(const Node& a, const Node& b);

std::vector<Node> get_neighbors(const Node& node, const std::vector<std::vector<int>>& grid);

std::vector<Node> reconstruct_path(Node* current);

std::vector<Node> astar(const std::vector<std::vector<int>>& grid, const Node& start, const Node& goal);

#endif // A_STAR_H
