#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {

  double bestProfit = 0.0;
  size_t buyIdx = 0;

  for (size_t i = 0; i < prices.size(); ++i)
  {
    const double currentprofit = prices[i] - prices[buyIdx];
    bestProfit = std::max(currentprofit, bestProfit);

    if (prices[buyIdx] > prices[i])
    {
      buyIdx = i;
    }
  }

  return bestProfit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
