#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct TreeNodeInfo
{
  int height;
  bool balanced;
};

TreeNodeInfo traverse(const unique_ptr<BinaryTreeNode<int>>& tree)
{
  if (!tree)
  {
    return {-1, true};
  }

  TreeNodeInfo leftInfo = traverse(tree->left);
  TreeNodeInfo rightInfo = traverse(tree->right);
  int leftH = leftInfo.height + 1;
  int rightH = rightInfo.height + 1;
  bool isBalanced = abs(leftH - rightH) <= 1 && leftInfo.balanced && rightInfo.balanced;

  return {std::max(leftH, rightH), isBalanced};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return traverse(tree).balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
