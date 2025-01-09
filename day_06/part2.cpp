/*
While using the same approach from part1 to simulate the guards path, the approach here
is to create a function check_for_loop() to detect if the given guard_map results in a loop.
This function is used to brute force check every possible location an additional obstacle could
be placed by iterating through the grid, adding an obstacle to a copy of guard_map, and using
check_for_loop() to determine if we add one to the result or not.

check_for_loop maintains a map of 4-tuple keys representing the obstacle and current location that gets checked
and then updated everytime an obstacle is reached in path simulation. If we have hit a obstacle from this position
already then we are in a loop and we return true early.
*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <unordered_map>

enum class Direction {
  up,
  down,
  left,
  right
};

struct four_int_hash {
  std::size_t operator()(const std::tuple<int, int, int, int>& key)
    const {
      auto [a, b, c, d] = key;
      std::size_t h1 = std::hash<int>{}(a);
      std::size_t h2 = std::hash<int>{}(b);
      std::size_t h3 = std::hash<int>{}(c);
      std::size_t h4 = std::hash<int>{}(d);
      return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

bool check_for_loop(
    int p_i,
    int p_j,
    int init_i,
    int init_j,
    std::vector<std::vector<int>> guard_map,
    std::vector<std::vector<int>> guard_path
    ) {
  std::unordered_map<std::tuple<int, int, int, int>, int, four_int_hash> map;
  guard_map[p_i][p_j] = 1;
  Direction dir = Direction::up;
  bool still_going = true;
  int i = init_i;
  int j = init_j;
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
          if (map.find(std::make_tuple(i-1,j,i,j)) != map.end()) {
            return true;
          } else {
            map[std::make_tuple(i-1,j,i,j)] = 1;
          }
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
          if (map.find(std::make_tuple(i+1,j,i,j)) != map.end()) {
            return true;
          } else {
            map[std::make_tuple(i+1,j,i,j)] = 1;
          }
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
          if (map.find(std::make_tuple(i,j-1,i,j)) != map.end()) {
            return true;
          } else {
            map[std::make_tuple(i,j-1,i,j)] = 1;
          }
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
          if (map.find(std::make_tuple(i,j+1,i,j)) != map.end()) {
            return true;
          } else {
            map[std::make_tuple(i,j+1,i,j)] = 1;
          }
        }
        break;
                             }
    }
  }
  return false;
}

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::vector<std::vector<int>> guard_map;
  std::vector<std::vector<int>> guard_path;
  std::vector<std::vector<int>> obs_map;
  int init_i, init_j;
  int i = 0;
  int j = 0;
  while (std::getline(f, line)) {
    std::vector<int> row_map;
    std::vector<int> row_path;
    std::vector<int> row_obs;
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
      row_obs.push_back(0);
      j++;
    }
    guard_map.push_back(row_map);
    guard_path.push_back(row_path);
    obs_map.push_back(row_obs);
    i++;
  }

  int result = 0;
  for (int p_i = 0; p_i < guard_map.size(); p_i++) {
    for (int p_j = 0; p_j < guard_map[p_i].size(); p_j++) {
      if (p_i == init_i && p_j == init_j) {
        printf("hit init spot, skipping\n");
      }
      else if (check_for_loop(p_i, p_j, init_i, init_j, guard_map, guard_path)) {
        result ++;
      }
    }
  }

  printf("%d\n", result);
}
