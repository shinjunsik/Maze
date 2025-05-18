// Maze.hpp
#pragma once
#include <vector>
#include <queue>
#include <utility>

class Maze {
public:
    int size;
    int width, height;
    std::vector<std::vector<int>> maze;
    std::pair<int, int> start, goal;

    Maze(int size);
    void generate();
    std::vector<std::pair<int, int>> findShortestPath();
    std::vector<std::vector<std::pair<int, int>>> findMultiplePaths(int max_paths);
    bool isValid(int x, int y);

    // Getter methods
    std::vector<std::vector<int>>& getMaze();
    std::pair<int, int> getStart() const;
    std::pair<int, int> getGoal() const;
    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<int>> getGrid() const;

private:
    void generate_iterative_dfs();
};
