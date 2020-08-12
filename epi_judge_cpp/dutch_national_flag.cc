#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using namespace std;
enum class Color { kRed, kWhite, kBlue };

// O(N) time, O(N) space sol'n
// void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
//   vector<Color>& A = *A_ptr;
//   const Color pivot = A[pivot_index];

//   vector<Color> lessP;
//   vector<Color> equalP;
//   vector<Color> greaterP;

//   for (const auto& color : A)
//   {
//     if (color < pivot)
//     {
//       lessP.push_back(color);
//     }
//     else if (color == pivot)
//     {
//       equalP.push_back(color);
//     }
//     else
//     {
//       greaterP.push_back(color);
//     }
//   }

//   A.clear();
//   A.insert(A.end(), lessP.begin(), lessP.end());
//   A.insert(A.end(), equalP.begin(), equalP.end());
//   A.insert(A.end(), greaterP.begin(), greaterP.end());

//   return;
// }

// O(N) time, O(1) space
void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  vector<Color>& A = *A_ptr;
  const Color pivot = A[pivot_index];

  size_t S = 0, E = 0, L = A.size();
  while (E < L)
  {
    Color current = A[E];
    if (current < pivot)
    {
      swap(A[S++], A[E++]);
    }
    else if (current > pivot)
    {
      // Move L first before swap because E moves after swap.
      // If both move after swap, we may end up with the case where E == L
      // and A[E] doesn't get inspected for that iteration.
      swap(A[--L], A[E]);
    }
    else
    {
      ++E;
    }
  }
  return;
}
void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
