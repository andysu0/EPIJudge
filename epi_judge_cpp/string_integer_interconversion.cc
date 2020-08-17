#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string result;
  const bool isNeg = x < 0;

  do
  {
    const int digit = abs(x % 10);
    result += '0' + digit;
    x /= 10;
  } while (x);

  if (isNeg)
  {
    result += '-';
  }

  return string(result.rbegin(), result.rend());
}
int StringToInt(const string& s) {
  if (s.empty())
  {
    return 0;
  }

  int result = 0;
  bool isNeg = s[0] == '-';
  size_t i = (isNeg || s[0] == '+') ? 1 : 0;

  for (; i < s.size(); ++i)
  {
    const int digit = s[i] - '0';
    result += digit * std::pow(10, s.size() - 1 - i);
  }

  return isNeg ? -result : result;
}

void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
