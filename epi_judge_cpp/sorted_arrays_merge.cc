#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct HeadNode
{
  int value;
  size_t arrNum;
  size_t arrIdx;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  auto cmp = [](const HeadNode& lhs, const HeadNode& rhs)
  {
    return lhs.value > rhs.value;
  };
  std::priority_queue<HeadNode, vector<HeadNode>, decltype(cmp)> minHeap(cmp);
  vector<int> result;

  for (size_t i = 0; i < sorted_arrays.size(); ++i)
  {
    if (!sorted_arrays[i].empty())
    {
      minHeap.push({sorted_arrays[i][0], i, 0});
    }
  }

  while (!minHeap.empty())
  {
    const auto& node = minHeap.top();
    result.push_back(node.value);

    size_t nextIdxInArr = node.arrIdx + 1;
    if (nextIdxInArr < sorted_arrays[node.arrNum].size())
    {
      minHeap.push({sorted_arrays[node.arrNum][nextIdxInArr], node.arrNum, nextIdxInArr});
    }

    minHeap.pop();
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
