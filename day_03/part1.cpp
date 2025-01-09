/*
The approach is to use a regex pattern to find a correct mul() pattern and then we can parse and multiply the numbers.
 */
#include <fstream>
#include <string>
#include <regex>

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::regex pattern(R"(mul\(([1-9]\d{0,2}),([1-9]\d{0,2})\))");
  int result = 0;
  int left, right;
  while (std::getline(f, line)) {
    std::sregex_iterator it(line.begin(), line.end(), pattern);
    std::sregex_iterator end;
    while (it != end) {
      std::smatch match = *it;
      left = std::stoi(match.str(1));
      right = std::stoi(match.str(2));
      result += left * right;
      ++it;
    }
  }
  printf("%d\n", result);
}
