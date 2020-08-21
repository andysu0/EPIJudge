#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

void DFS(const unique_ptr<BinaryTreeNode<int>>& tree, int& visitedVal, bool& isBST) {

  if (tree->left)
  {
    DFS(tree->left, visitedVal, isBST);
  }

  if (tree->data < visitedVal)
    isBST = false;

  visitedVal = tree->data;

  if (tree->right)
  {
    DFS(tree->right, visitedVal, isBST);
  }
}
bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree)
  {
    return true;
  }

  bool isBST = true;
  int visitedVal = std::numeric_limits<int>::min();
  DFS(tree, visitedVal, isBST);

  return isBST;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
