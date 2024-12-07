#include <fstream>
#include <vector>
#include <string>

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::vector<std::vector<int>> guard_map;
  std::vector<std::vector<int>> guard_path;
  int init_i, init_j;
  int i = 0;
  int j = 0;
  while (std::getline(f, line)) {
    std::vector<int> row_map;
    std::vector<int> row_path;
    j = 0;
    for (const auto& c : line) {
      if (c == '#') {
        row_map.push_back(1);
      } else if (c == '^') {
        init_i = i;
        init_j = j;
      } else {
        row_map.push_back(0);
      }
      row_path.push_back(0);
      j++;
    }
    guard_map.push_back(row_map);
    guard_path.push_back(row_path);
    i++;
  }

  enum class Direction {
    up,
    down,
    left,
    right
  };
  Direction dir = Direction::up;
  bool still_going = true;
  while (still_going) {
    switch (dir) {
      case Direction::up: {
        while (i >= 0 && guard_map[i][j] != 1) {
          guard_path[i][j] = 1;
          i--;
        }
        i++;
        if (i == 0) {
          still_going = false;
        } else {
          dir = Direction::right;
        }
        break;
                          }
      case Direction::down: {
        while (i < guard_map.size() && guard_map[i][j] != 1) {
          guard_path[i][j] = 1;
          i++;
        }
        i--;
        if (i == guard_map.size() - 1) {
          still_going = false;
        } else {
          dir = Direction::left;
        }
        break;
                           }
      case Direction::left: {
        while (j >= 0 && guard_map[i][j] != 1) {
          guard_path[i][j] = 1;
          j--;
        }
        j++;
        if (j == 0) {
          still_going = false;
        } else {
          dir = Direction::up;
        }
        break;
                            }
      case Direction::right: {
        while (j < guard_map[0].size() && guard_map[i][j] != 1) {
          guard_path[i][j] = 1;
          j++;
        }
        j--;
        if (j == guard_map[0].size() - 1) {
          still_going = false;
        } else {
          dir = Direction::down;
        }
        break;
                             }
    }
  }

  int result = 0;
  for (int i = 0; i<guard_path.size(); i++) {
    for (int j = 0; j < guard_path[i].size(); j++) {
      if (guard_path[i][j] == 1) result++;
    }
    printf("%d\n", result);
  }
}
