/*
The approach is to parse data into a 2-d grid and then iterate through looking for X's.
For each X we can do 2-d array look-ups for each possible XMAS pattern involving that X and return
the count.
 */
#include <fstream>
#include <string>
#include <vector>

int find_matches(std::vector<std::vector<char>> &grid, int i, int j) {
  int num_matches = 0;
  // left
  if (j > 2) {
    if (grid[i][j-1] == 'M' && grid[i][j-2] == 'A' && grid[i][j-3] == 'S') {
      num_matches += 1;
    }
  }
  // right
  if (j < grid[i].size() - 3) {
    if (grid[i][j+1] == 'M' && grid[i][j+2] == 'A' && grid[i][j+3] == 'S') {
      num_matches += 1;
    }
  }
  // up
  if (i > 2) {
    if (grid[i-1][j] == 'M' && grid[i-2][j] == 'A' && grid[i-3][j] == 'S') {
      num_matches += 1;
    }
  }
  // down
  if (i < grid.size() - 3) {
    if (grid[i+1][j] == 'M' && grid[i+2][j] == 'A' && grid[i+3][j] == 'S') {
      num_matches += 1;
    }
  }
  // top-left
  if (i > 2 && j > 2) {
    if (grid[i-1][j-1] == 'M' && grid[i-2][j-2] == 'A' && grid[i-3][j-3] == 'S') {
      num_matches += 1;
    }
  }
  // top-right
  if (i > 2 && j < grid[i].size() - 3) {
    if (grid[i-1][j+1] == 'M' && grid[i-2][j+2] == 'A' && grid[i-3][j+3] == 'S') {
      num_matches += 1;
    }
  }
  // bot-left
  if (i < grid.size() - 3 && j > 2) {
    if (grid[i+1][j-1] == 'M' && grid[i+2][j-2] == 'A' && grid[i+3][j-3] == 'S') {
      num_matches += 1;
    }
  }
  // bot-right
  if (i < grid.size() - 3 && j < grid[i].size() - 3) {
    if (grid[i+1][j+1] == 'M' && grid[i+2][j+2] == 'A' && grid[i+3][j+3] == 'S') {
      num_matches += 1;
    }
  }

  return num_matches;
}

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::vector<std::vector<char>> grid;

  // parse input into a 2d array
  while (std::getline(f, line)) {
    std::vector<char> curr_row;
    for (auto& c : line) {
      curr_row.push_back(c);
    }
    grid.push_back(curr_row);
  }

  // iterate looking for X's
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'X') {
        result += find_matches(grid, i, j);
      }
    }
  }

  printf("%d\n", result);
}
