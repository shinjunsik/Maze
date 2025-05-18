
#include "MazeExporter.hpp"
#include "json.hpp"
#include <fstream>
#include <sstream>

using json = nlohmann::json;

void exportMazeToJson(const Maze& maze, const std::vector<Monster>& monsters, const std::string& filename) {
    json j;

    // map (with space-separated string format for readability)
    j["map"] = json::array();
    const auto& grid = maze.getGrid();
    for (const auto& row : grid) {
        std::stringstream ss;
        for (size_t i = 0; i < row.size(); ++i) {
            ss << row[i];
            if (i + 1 < row.size()) ss << " ";
        }
        j["map"].push_back(ss.str());
    }

    // player position (start)
    auto start = maze.getStart();
    j["player_start"] = { start.first, start.second };

    // goal position
    auto goal = maze.getGoal();
    j["goal"] = { goal.first, goal.second };

    // monster count
    j["monster_count"] = static_cast<int>(monsters.size());

    // monsters with binary pattern
    j["monsters"] = json::array();
    for (const auto& monster : monsters) {
        const auto& path = monster.getPath();
        if (path.size() < 2) continue;

        json monsterJson;
        auto startPos = path[0];
        monsterJson["start"] = { startPos.first, startPos.second };

        auto getBinaryDir = [](int dx, int dy) {
            if (dx == -1 && dy == 0) return "10"; // Left
            if (dx == 1 && dy == 0) return "11"; // Right
            if (dx == 0 && dy == -1) return "00"; // Up
            if (dx == 0 && dy == 1) return "01"; // Down
            return "??"; // Error fallback
            };

        json patternArray = json::array();
        for (size_t i = 1; i < path.size(); ++i) {
            int dy = path[i].first - path[i - 1].first;
            int dx = path[i].second - path[i - 1].second;
            std::string dirCode = getBinaryDir(dx, dy);
            patternArray.push_back(dirCode);
        }

        monsterJson["pattern"] = patternArray;
        j["monsters"].push_back(monsterJson);
    }

    std::string path = filename.empty() ? "output_maze.json" : filename;

    std::ofstream out(path);
    out << j.dump(4);  // pretty print
}
