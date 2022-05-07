// https://leetcode-cn.com/problems/string-to-integer-atoi/
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int myAtoi(std::string s) {
    int res = 0;
    int sign = 1;
    State state = kStateStart;

    for (auto c : s) {
      parse(c, state, res, sign);
      if (state == kStateEnd) break;
    }

    return res * sign;
  }

 private:
  enum Character {
    kCharSpace = 0,
    kCharSign,
    kCharNumber,
    kCharOther,
  };

  enum State {
    kStateStart = 0,
    kStateSigned,
    kStateInNumber,
    kStateEnd,
  };

  std::unordered_map<State, std::unordered_map<Character, State>> transfer = {
      {kStateStart,
       {{kCharSpace, kStateStart},
        {kCharSign, kStateSigned},
        {kCharNumber, kStateInNumber},
        {kCharOther, kStateEnd}}},
      {kStateSigned,
       {{kCharSpace, kStateEnd},
        {kCharSign, kStateEnd},
        {kCharNumber, kStateInNumber},
        {kCharOther, kStateEnd}}},
      {kStateInNumber,
       {{kCharSpace, kStateEnd},
        {kCharSign, kStateEnd},
        {kCharNumber, kStateInNumber},
        {kCharOther, kStateEnd}}},
      {kStateEnd,
       {{kCharSpace, kStateEnd},
        {kCharSign, kStateEnd},
        {kCharNumber, kStateEnd},
        {kCharOther, kStateEnd}}},
  };

  Character get_character(char c) {
    if (c == ' ') return kCharSpace;
    if (c == '+' || c == '-') return kCharSign;
    if (std::isdigit(c)) return kCharNumber;
    return kCharOther;
  }

  void parse(char c, State& state, int& res, int& sign) {
    state = transfer[state][get_character(c)];
    if (state == kStateInNumber) {
      if (res > INT_MAX / 10 || (res == INT_MAX / 10 && (c - '0' > 7))) {
        res = sign == 1 ? INT_MAX : INT_MIN;
        state = kStateEnd;
        return;
      }
      res = res * 10 + c - '0';
    } else if (state == kStateSigned) {
      sign = c == '+' ? 1 : -1;
    }
  }
};

int main() {
  std::string s = " -10100230o4";

  Solution solution;
  std::cout << solution.myAtoi(s) << std::endl;
}
