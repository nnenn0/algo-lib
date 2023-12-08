#include <iostream>
#include <vector>

using namespace std;

/*

nを素因数分解する。

*/

vector<pair<long long, long long>> prime_factorize(long long n) {
  vector<pair<long long, long long>> res;
  for (long long p = 2; p * p <= n; ++p) {
    if (n % p != 0) continue;
    long long num = 0;
    while (n % p == 0) {
      ++num;
      n /= p;
    }
    res.push_back(make_pair(p, num));
  }
  if (n != 1) res.push_back(make_pair(n, 1));
  return res;
}

int main() {
  int n = 777;
  auto res = prime_factorize(n);
  for (auto& num : res) {
    cout << "{ " << num.first << ", " << num.second << " }" << endl;
  }
  /*
  { 3, 1 }
  { 7, 1 }
  { 37, 1 }
  */
}