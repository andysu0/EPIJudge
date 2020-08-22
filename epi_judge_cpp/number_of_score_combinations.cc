#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores)
{
  vector<vector<int>> cache;
  cache.resize(individual_play_scores.size(), std::vector<int>(final_score + 1, 0));

  for (int i = 0; i < individual_play_scores.size(); ++i)
  {
    cache[i][0] = 1;
    for (int j = 1; j <= final_score; ++j)
    {
      int combi = 0;

      if (i - 1 >= 0)
      {
        combi += cache[i - 1][j];
      }

      if (j - individual_play_scores[i] >= 0)
      {
        combi += cache[i][j - individual_play_scores[i]];
      }

      cache[i][j] = combi;
    }
  }

  return cache.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
