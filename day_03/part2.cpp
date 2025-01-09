/*
  The approach is for each line we will iterate through the mul(X,Y) matches and the do() matches
  keeping track of if we are in a do() or don't() state for the current mul match
  by using the ->position() of the regex matches to be sure we are keeping the most
  recent do_state for the current mul match we are processing. We can then carry out the valid multiplies.
 */
#include <fstream>
#include <string>
#include <regex>
#include <iostream>

int main() {
  std::ifstream f("input.txt");
  std::string line;
  std::regex pattern_mul(R"(mul\(([1-9]\d{0,2}),([1-9]\d{0,2})\))");
  std::regex pattern_do(R"(do(?:n't)?\(\))");
  int result = 0;
  int left, right;
  bool do_state = true;
  // for each line we will iterate through the mul(X,Y) matches and the do() matches
  // keeping track of if we are in a do() or don't() state for the current mul match
  // by using the ->position() of the regex matches to be sure we are keeping the most
  // recent do_state for the current mul match we are processing
  while (std::getline(f, line)) {
    std::sregex_iterator it_mul(line.begin(), line.end(), pattern_mul);
    std::sregex_iterator it_do(line.begin(), line.end(), pattern_do);
    std::sregex_iterator end;
    std::smatch curr_do = *it_do;
    while (it_mul != end) {
      // iterate the do matches to get the most recent do_state updated
      while (it_do->position() < it_mul->position() && it_do != end) {
        if ((*it_do).str().length() < 5) {
          do_state = true;
        } else {
          do_state = false;
        }
        ++it_do;
      }
      // if we are in the right do state we will carry out the multiply and update result
      std::smatch curr_mul = *it_mul;
      left = std::stoi(curr_mul.str(1));
      right = std::stoi(curr_mul.str(2));
      if (do_state) result += left * right;
      ++it_mul;
    }
    // if there are more do matches after iterating through all the mul matches in the current line
    // then we need to update the do_state by iterating over all remaining do matches
    if (it_do != end) {
      while (it_do != end) {
        if ((*it_do).str().length() < 3) {
          do_state = true;
        } else {
          do_state = false;
        }
        ++it_do;
      }
    }
  }
  printf("%d\n", result);
}
