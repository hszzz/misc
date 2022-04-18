// https://leetcode-cn.com/problems/add-strings

class Solution {
 public:
  string addStrings(string num1, string num2) {
    string res;
    int pos1 = num1.size() - 1;
    int pos2 = num2.size() - 1;
    bool carry = false;

    while (pos1 >= 0 && pos2 >= 0) {
      int num = static_cast<int>(num1[pos1--] - '0') +
                static_cast<int>(num2[pos2--] - '0');

      num = carry ? num + 1 : num;
      if (num > 9) {
        num = num - 10;
        carry = true;
      } else {
        carry = false;
      }

      res.push_back('0' + num);
    }

    while (pos1 >= 0) {
      int num = static_cast<int>(num1[pos1--] - '0');

      num = carry ? num + 1 : num;
      if (num > 9) {
        num = num - 10;
        carry = true;
      } else {
        carry = false;
      }

      res.push_back('0' + num);
    }

    while (pos2 >= 0) {
      int num = static_cast<int>(num2[pos2--] - '0');

      num = carry ? num + 1 : num;
      if (num > 9) {
        num = num - 10;
        carry = true;
      } else {
        carry = false;
      }

      res.push_back('0' + num);
    }

    if (carry) res.push_back('1');

    std::reverse(res.begin(), res.end());
    return res;
  }
};
