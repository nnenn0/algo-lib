#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*

nの約数を全て列挙する。

*/

vector<long long> divisor(long long n) {
  vector<long long> ret;
  for (long long i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      ret.push_back(i);
      if (i * i != n) ret.push_back(n / i);
    }
  }
  sort(ret.begin(), ret.end());
  return ret;
}

int main() {
  auto res = divisor(100);
  for (auto val : res) cout << val << endl;
}