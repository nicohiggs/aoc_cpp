/*
Here we are able to brute force dropping one number at a time and checking it is still safe
 */
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool is_safe(std::vector<int>& report) {
  bool increasing = report[1] > report[0] ? true : false;
  int prev, curr;
  for (int i = 1; i < report.size(); i++) {
    prev = report[i-1];
    curr = report[i];
    if (increasing) {
      if (curr <= prev) return false;
      if ((curr - prev) > 3) return false;
    } else {
      if (curr >= prev) return false;
      if ((prev - curr) > 3) return false;
    }
  }
  return true;
}

bool is_safe2(std::vector<int>& report) {
  for (int i = 0; i < report.size(); i++) {
    std::vector<int> drop1 = report;
    drop1.erase(drop1.begin() + i);
    if (is_safe(drop1)) return true;
  }
  return false;
}

int main() {
  std::ifstream f("input.txt");
  std::string line;
  int num_safe = 0;
  while (std::getline(f, line)) {
    std::vector<int> curr_report;
    std::istringstream iss(line);
    std::string num;
    while (std::getline(iss, num, ' ')) {
      curr_report.push_back(std::stoi(num));
    }

    if (is_safe2(curr_report)) num_safe += 1;

  }
  
  printf("%d\n", num_safe);
}
