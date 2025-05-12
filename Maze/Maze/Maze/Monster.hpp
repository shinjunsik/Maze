#pragma once
#include <vector>
#include <chrono>
#include <utility>

class Monster {
public:
    Monster();
    Monster(const std::vector<std::pair<int, int>>& path);

    void update();
    std::pair<int, int> getPosition() const;
    const std::vector<std::pair<int, int>>& getPath() const;

    // ✅ 새로 추가된 정적 함수: 섹터 기반 몬스터 자동 생성
    static std::vector<Monster> generateMonsters(int monster_count, const std::vector<std::vector<int>>& maze);
    std::vector<std::vector<int>> getGrid() const;

private:
    std::vector<std::pair<int, int>> path;
    int current_index;
    int direction;
    std::chrono::steady_clock::time_point last_move_time;

    const float moveInterval = 0.5f; // 이동 간격 (초 단위)
};
