#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  
    if (n < 2)
        return {};

    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    std::vector<int> primes;

    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);

            for (int j = i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
