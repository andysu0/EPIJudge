#include "test_framework/generic_test.h"

int ChangeMaking(int cents) {
  const std::array<int, 6> coins = {100, 50, 25, 10, 5, 1};

  int minNumCoins = 0;
  for(int i = 0; i < coins.size(); ++i)
  {
    minNumCoins += cents / coins[i];
    cents = cents % coins[i];
  }

  return minNumCoins;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"cents"};
  return GenericTestMain(args, "making_change.cc", "making_change.tsv",
                         &ChangeMaking, DefaultComparator{}, param_names);
}
