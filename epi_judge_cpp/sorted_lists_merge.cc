#include "list_node.h"
#include "test_framework/generic_test.h"
#include <memory>

shared_ptr<ListNode<int>> MergeTwoSortedListsRecursive(shared_ptr<ListNode<int>> L1,
                                                       shared_ptr<ListNode<int>> L2)
{
  if (!L1)
    return L2;

  if (!L2)
    return L1;

  if (L1->data < L2->data)
  {
    L1->next = MergeTwoSortedListsRecursive(L1->next, L2);
    return L1;
  }
  else
  {
    L2->next = MergeTwoSortedListsRecursive(L1, L2->next);
    return L2;
  }
}

void append(shared_ptr<ListNode<int>>& curNode, shared_ptr<ListNode<int>>& newNode)
{
  if (curNode)
    curNode->next = newNode;

  curNode = newNode;
}

shared_ptr<ListNode<int>> MergeTwoSortedListsIterative(shared_ptr<ListNode<int>> L1,
                                                       shared_ptr<ListNode<int>> L2)
{
  auto fakeHead = std::make_shared<ListNode<int>>();
  shared_ptr<ListNode<int>> tail = fakeHead;

  while (L1 && L2)
  {
    if (L1->data < L2->data)
    {
      append(tail, L1);
      L1 = L1->next;
    }
    else
    {
      append(tail, L2);
      L2 = L2->next;
    }
  }

  tail->next = L1 ? L1 : L2;

  return fakeHead->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  // return MergeTwoSortedListsIterative(L1, L2);
  return MergeTwoSortedListsRecursive(L1, L2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
