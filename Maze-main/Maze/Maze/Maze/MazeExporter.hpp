#pragma once
#include "Maze.hpp"
#include "Monster.hpp"
#include <vector>
#include <string>

// filename 인자는 기본값으로 빈 문자열을 허용 (필수가 아님)
void exportMazeToJson(const Maze& maze, const std::vector<Monster>& monsters, const std::string& filename = "");
