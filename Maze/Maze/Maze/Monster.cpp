#include "Monster.hpp"
#include <random>

Monster::Monster() : current_index(0), direction(1) {
    last_move_time = std::chrono::steady_clock::now();
}

Monster::Monster(const std::vector<std::pair<int, int>>& path)
    : path(path), current_index(0), direction(1) {
    last_move_time = std::chrono::steady_clock::now();
}

void Monster::update() {
    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - last_move_time).count();

    if (elapsed > moveInterval) {
        current_index += direction;

        if (current_index >= (int)path.size()) {
            current_index = path.size() - 2;
            direction = -1;
        }
        else if (current_index < 0) {
            current_index = 1;
            direction = 1;
        }

        last_move_time = now;
    }
}

std::pair<int, int> Monster::getPosition() const {
    if (path.empty()) return { -1, -1 };
    return path[current_index];
}

const std::vector<std::pair<int, int>>& Monster::getPath() const {
    return path;
}

std::vector<Monster> Monster::generateMonsters(int monster_count, const std::vector<std::vector<int>>& maze) {
    std::vector<Monster> monsters;

    int height = maze.size();
    int width = maze[0].size();

    int sector_rows = 3;
    int sector_cols = 3;
    int sector_height = height / sector_rows;
    int sector_width = width / sector_cols;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> offset_dist(-1, 1);

    for (int i = 0; i < sector_rows; ++i) {
        for (int j = 0; j < sector_cols; ++j) {
            if ((int)monsters.size() >= monster_count) break;

            int cx = i * sector_height + sector_height / 2;
            int cy = j * sector_width + sector_width / 2;

            if (cx % 2 == 0) cx++;
            if (cy % 2 == 0) cy++;

            int x = cx + offset_dist(gen) * 2;
            int y = cy + offset_dist(gen) * 2;

            if (x > 0 && x < height - 1 && y > 0 && y < width - 1 && maze[x][y] == 0) {
                std::vector<std::pair<int, int>> path = { {x, y} };
                monsters.emplace_back(path);
            }
        }
    }

    return monsters;
}
