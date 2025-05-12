#pragma once
#include "Maze.hpp"
#include "Monster.hpp"
#include <vector>
#include <string>

// filename ���ڴ� �⺻������ �� ���ڿ��� ��� (�ʼ��� �ƴ�)
void exportMazeToJson(const Maze& maze, const std::vector<Monster>& monsters, const std::string& filename = "");
