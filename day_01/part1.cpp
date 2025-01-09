/*
We parse into 2 lists, sort them, and then compute pairwise differences.
 */
#include <vector>
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
  while (std::getline(f, line)) {
    n1 = std::stoi(line.substr(0, 5));
    n2 = std::stoi(line.substr(8));
    llist.push_back(n1);
    rlist.push_back(n2);
  }

  std::sort(llist.begin(), llist.end());
  std::sort(rlist.begin(), rlist.end());

  int diffs = 0;
  for (int i = 0; i < llist.size(); i++) {
    if (llist[i] > rlist[i]) {
      diffs += llist[i] - rlist[i];
    } else {
      diffs += rlist[i] - llist[i];
    }
  }

  printf("%d", diffs);
}
