#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::unordered_map<int, std::vector<int>> page_orders;

  bool not_reached = true;
  int num1, num2;
  int result = 0;
  while (std::getline(f, line)) {
    if (not_reached) {
      // parsing page orders
      if (line.length() == 0) {
        not_reached = false;
      } else {
        num1 = std::stoi(line.substr(0, 2));
        num2 = std::stoi(line.substr(3, 2));

        if (page_orders.find(num1) != page_orders.end()) {
          page_orders[num1].push_back(num2);
        } else {
          std::vector<int> newvec;
          page_orders[num1] = newvec;
          page_orders[num1].push_back(num2);
        }
      }
    } else {
      // parsing updates
      int curr_num;
      std::vector<int> update;
      for (int i = 0; i < line.length() - 1; i += 3) {
        curr_num = std::stoi(line.substr(i, 2));
        update.push_back(curr_num);
      }
      // check update is valid
      bool valid = true;
      for (int i = update.size() - 1; i > 0; i--) {
        for (int j = i-1; j >= 0; j--) {
          for (const auto& n : page_orders[update[i]]) {
            if (update[j] == n) {
              valid = false;
            }
          }
        }
      }
      if (valid) {
        result += update[update.size() / 2];
      }
    }
  }
  printf("%d\n", result);
}
