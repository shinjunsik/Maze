// Maze.cpp
#include "Maze.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include <stack>
#include <utility>
#include <vector>

Maze::Maze(int size) : size(size) {
    width = height = size + 2;

    // ��ü�� ��(1)���� �ʱ�ȭ
    maze.resize(height, std::vector<int>(width, 1));

    // �������� ������ ����
    start = { 1, 1 };
    goal = { height - 2, width - 2 };

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Maze::generate_iterative_dfs() {
    std::stack<std::pair<int, int>> stk;
    maze[start.first][start.second] = 0;
    stk.push(start);

    static const int dx[] = { -2, 2, 0, 0 };
    static const int dy[] = { 0, 0, -2, 2 };
    std::random_device rd;
    std::mt19937 g(rd());

    while (!stk.empty()) {
        std::pair<int, int> current = stk.top();
        int x = current.first;
        int y = current.second;
        stk.pop();

        std::vector<int> dir = { 0, 1, 2, 3 };
        std::shuffle(dir.begin(), dir.end(), g);

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[dir[i]];
            int ny = y + dy[dir[i]];
            if (this->isValid(nx, ny) && this->maze[nx][ny] == 1) {
                this->maze[(x + nx) / 2][(y + ny) / 2] = 0;
                this->maze[nx][ny] = 0;
                stk.push({ x, y });
                stk.push({ nx, ny });
                break;
            }
        }
    }
}


void Maze::generate() {
    // �������� ��� �հ� dfs ����
    generate_iterative_dfs();

    // goal�� ������ ����
    maze[goal.first][goal.second] = 0;

    // goal �ֺ� ���� ����
    bool connected = false;
    static const int dx[] = { -1, 1, 0, 0 };
    static const int dy[] = { 0, 0, -1, 1 };
    for (int d = 0; d < 4; ++d) {
        int nx = goal.first + dx[d];
        int ny = goal.second + dy[d];
        if (isValid(nx, ny) && maze[nx][ny] == 0) {
            connected = true;
            break;
        }
    }
    if (!connected) {
        maze[goal.first - 1][goal.second] = 0;
    }

    // �ִ� ��� �ϳ� Ȯ��
    auto path = findShortestPath();

    // goal ��ó�� �ִ� ���� ��� 1~2�� �� �վ��� (��ȸ ��� ����)
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<std::pair<int, int>> candidates;
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if (maze[i][j] == 1) {
                int count = 0;
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (isValid(ni, nj) && maze[ni][nj] == 0) {
                        count++;
                    }
                }
                if (count >= 2) candidates.emplace_back(i, j);
            }
        }
    }

    std::shuffle(candidates.begin(), candidates.end(), gen);
    int num_to_open = std::min(2, (int)candidates.size());
    for (int i = 0; i < num_to_open; ++i) {
        maze[candidates[i].first][candidates[i].second] = 0;
    }
}

bool Maze::isValid(int x, int y) {
    return x > 0 && x < height - 1 && y > 0 && y < width - 1;
}

std::vector<std::pair<int, int>> Maze::findShortestPath() {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::pair<int, int>>> parent(height, std::vector<std::pair<int, int>>(width, { -1, -1 }));
    std::queue<std::pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    static const int dx[] = { -1, 1, 0, 0 };
    static const int dy[] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == goal.first && y == goal.second) break;

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (isValid(nx, ny) && maze[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = { x, y };
                q.push({ nx, ny });
            }
        }
    }

    std::vector<std::pair<int, int>> path;
    for (auto at = goal; at != std::make_pair(-1, -1); at = parent[at.first][at.second]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::vector<std::pair<int, int>>> Maze::findMultiplePaths(int max_paths) {
    std::vector<std::vector<std::pair<int, int>>> paths;
    paths.push_back(findShortestPath());
    // TODO: �� ���� ��θ� Ȯ���ϵ��� ����
    return paths;
}

// Getter �޼����
std::vector<std::vector<int>>& Maze::getMaze() { return maze; }
std::pair<int, int> Maze::getStart() const { return start; }
std::pair<int, int> Maze::getGoal() const { return goal; }
int Maze::getWidth() const { return width; }
int Maze::getHeight() const { return height; }

std::vector<std::vector<int>> Maze::getGrid() const {
    return maze;
}
