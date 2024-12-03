#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

int main() {
  std::ifstream f("input.txt");
  std::string line;
  int n1, n2;
  std::vector<int> llist;
  std::vector<int> rlist;
  std::unordered_map<int, int> rmap;
  while (std::getline(f, line)) {
    n1 = std::stoi(line.substr(0, 5));
    n2 = std::stoi(line.substr(8));
    llist.push_back(n1);
    if (rmap.find(n2) != rmap.end()) {
      rmap[n2] += 1;
    } else {
      rmap[n2] = 1;
    }
  }

  int result = 0;
  for (int i = 0; i < llist.size(); i++) {
    if (rmap.find(llist[i]) != rmap.end()) {
      result += llist[i] * rmap[llist[i]];
    }
  }

  printf("%d", result);
}
