
#include "MazeRunner.hpp"
#include <iostream>

int main() {
    int stage;
    std::cout << "단계 입력: ";
    std::cin >> stage;

    for (int i = 0; i <= 4; ++i) {
        std::cout << "[ " << i << " / 5 ] 미로 생성 중..." << std::endl;
        generateMazeStage(stage, "maze" + std::to_string(i) + ".json");
    }

    std::cout << "모든 미로 생성 완료!" << std::endl;
    return 0;
}
