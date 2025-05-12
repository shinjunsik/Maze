
#include <iostream>
#include <vector>
#include <set>
#include "Maze.hpp"
#include "Monster.hpp"
#include "MazeExporter.hpp"  // ✅ JSON 저장 기능 포함

int main() {
    int size, monster_count;
    std::cout << "맵 크기(size x size): ";
    std::cin >> size;
    std::cout << "몬스터 수: ";
    std::cin >> monster_count;

    Maze maze(size);
    maze.generate();

    auto path = maze.findShortestPath();
    std::vector<Monster> monsters;
    std::set<std::pair<int, int>> monster_path_cells;

    std::cout << "\n[몬스터 이동 경로 생성]" << std::endl;
    for (int i = 0; i < monster_count; ++i) {
        if (path.size() < 10) break;

        int base = path.size() / 3 + rand() % (path.size() / 3);
        std::pair<int, int> mid = path[base];

        // mid 근처 벽 뚫고 우회 경로 확장
        std::vector<std::pair<int, int>> extension;
        static const int dx[] = { -1, 1, 0, 0 };
        static const int dy[] = { 0, 0, -1, 1 };

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

        std::cout << "몬스터 " << i << ": ";
        for (const auto& p : monster_path) {
            std::cout << "(" << p.first << "," << p.second << ") ";
        }
        std::cout << "\n";
    }

    std::cout << "\n[미로 출력]\n";
    for (int i = 0; i < maze.getHeight(); ++i) {
        for (int j = 0; j < maze.getWidth(); ++j) {
            std::pair<int, int> pos = { i, j };
            if (pos == maze.getStart()) std::cout << "S ";
            else if (pos == maze.getGoal()) std::cout << "G ";
            else if (monster_path_cells.count(pos)) std::cout << "M ";
            else std::cout << (maze.getMaze()[i][j] ? "# " : ". ");
        }
        std::cout << '\n';
    }

    // ✅ JSON 파일로 미로 + 몬스터 정보 저장
    exportMazeToJson(maze, monsters);

    return 0;
}
