
#include "Maze.hpp"
#include "Monster.hpp"
#include "MazeExporter.hpp"
#include "MazeRunner.hpp"
#include <set>
#include <random>
#include <string>

void generateMazeStage(int stage) {
    generateMazeStage(stage, "output_maze.json");
}

void generateMazeStage(int stage, const std::string& filename) {
    int size = 11 + (stage - 1) * 2;
    int monster_count = 2 + stage;

    Maze maze(size);
    maze.generate();

    auto path = maze.findShortestPath();
    std::vector<Monster> monsters;
    std::set<std::pair<int, int>> monster_path_cells;

    int segment = std::max(1, (int)path.size() / monster_count);
    for (int i = 0; i < monster_count; ++i) {
        int start = i * segment;
        int end = std::min((i + 1) * segment, (int)path.size()) - 1;
        if (start >= end) continue;

        int base = start + rand() % (end - start + 1);
        std::pair<int, int> mid = path[base];

        static const int dx[] = { -1, 1, 0, 0 };
        static const int dy[] = { 0, 0, -1, 1 };
        std::vector<std::pair<int, int>> extension;

        for (int d = 0; d < 4; ++d) {
            int nx = mid.first + dx[d];
            int ny = mid.second + dy[d];
            if (maze.isValid(nx, ny) && maze.getMaze()[nx][ny] == 1) {
                maze.getMaze()[nx][ny] = 0;
                extension.push_back({ nx, ny });
                break;
            }
        }

        std::vector<std::pair<int, int>> monster_path = extension;
        for (int j = 0; j < 5 && base + j < path.size(); ++j) {
            monster_path.push_back(path[base + j]);
        }

        monsters.emplace_back(monster_path);
        monster_path_cells.insert(monster_path.begin(), monster_path.end());
    }

    exportMazeToJson(maze, monsters, filename);
}
