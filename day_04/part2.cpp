/*
The approach is to parse the input into a 2-d grid and then iterate through it looking for the A's.
Then check for the X-MAS pattern at each A.
 */
#include <fstream>
#include <string>
#include <vector>

bool is_xmas(std::vector<std::vector<char>> &grid, int i, int j) {
  // valid coords to check
  if (j == 0 || i == 0 || j == grid[i].size() - 1 || i == grid.size() - 1) {
    return false;
  }
  if (((grid[i-1][j-1] == 'M' && grid[i+1][j+1] == 'S') || (grid[i-1][j-1] == 'S' && grid[i+1][j+1] == 'M')) &&
      ((grid[i+1][j-1] == 'M' && grid[i-1][j+1] == 'S') || (grid[i+1][j-1] == 'S' && grid[i-1][j+1] == 'M'))) {
    return true;
  }
  return false;
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

  // iterate looking for A's
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 'A' && is_xmas(grid, i, j)) {
        result++;
      }
    }
  }

  printf("%d\n", result);
}
