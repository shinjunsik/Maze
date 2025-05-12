
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

    // full monster paths
    j["monsters"] = json::array();
    for (const auto& monster : monsters) {
        std::ostringstream oss;
        oss << "[";
        const auto& path = monster.getPath();
        for (size_t i = 0; i < path.size(); ++i) {
            oss << "(" << path[i].first << ", " << path[i].second << ")";
            if (i + 1 < path.size()) oss << ", ";
        }
        oss << "]";
        j["monsters"].push_back(oss.str());
    }

    std::string path = filename.empty() ? "output_maze.json" : filename;

    std::ofstream out(path);
    out << j.dump(4);  // pretty print
}
