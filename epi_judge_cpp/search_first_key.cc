#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  int L = 0, U = A.size() - 1;

  while (L <= U)
  {
    int mid = L + (U - L) / 2;
    if (k < A[mid])
    {
      U = mid - 1;
    }
    else if (k > A[mid])
    {
      L = mid + 1;
    }
    else
    {
      // k == A[mid]
      while (mid >= 0 && A[mid] == k)
      {
        --mid;
      }

      return mid + 1;
    }
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
