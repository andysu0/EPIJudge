#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
  std::sort(A.begin(), A.end());

  for (int i = 0; i < A.size(); ++i)
  {
    int target = t - A[i];
    int j = 0, k = A.size() - 1;
    while (j <= k)
    {
      int sum = A[j] + A[k];
      if (sum > target)
      {
        --k;
      }
      else if (sum < target)
      {
        ++j;
      }
      else
        return true;
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
