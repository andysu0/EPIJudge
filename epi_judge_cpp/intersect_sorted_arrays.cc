#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  auto itA = A.begin();
  auto itB = B.begin();

  vector<int> result;
  while (itA != A.end() && itB != B.end())
  {
    int valA = *itA;
    int valB = *itB;

    if (valA < valB)
    {
      ++itA;
    }
    else if (valA > valB)
    {
      ++itB;
    }
    else
    {
      if (result.empty() || result.back() != valA)
      {
        result.push_back(valA);
      }
      ++itA;
      ++itB;
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
