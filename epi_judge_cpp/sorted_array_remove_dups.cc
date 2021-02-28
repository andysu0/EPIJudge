#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

// [1 1 1 2 2 3 3]
// [1 2 3]

// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
    auto& A = *A_ptr;
    if (A.empty())
        return 0;

    int writeIdx = 1;
    for (size_t i = 0; i < A.size(); ++i)
    {
        if (A[writeIdx - 1] != A[i])
        {
            A[writeIdx] = A[i];
            ++writeIdx;
        }
    }

    A.resize(writeIdx);

    return writeIdx;
}

vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
