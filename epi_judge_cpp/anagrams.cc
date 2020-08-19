#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  std::unordered_map<string, vector<string>> map;

  for (const auto& s : dictionary)
  {
    string sorted_s(s);
    std::sort(sorted_s.begin(), sorted_s.end());
    map[sorted_s].push_back(s);
  }

  vector<vector<string>> result;
  for (const auto& item : map)
  {
    if (item.second.size() > 1)
    {
      result.push_back(item.second);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
