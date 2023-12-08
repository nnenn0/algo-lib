#include <iostream>
#include <numeric>
#include <vector>

/*

素因数分解を高速で行う。
前処理 O(NloglogN)
計算量 O(logN)

*/

std::vector<long long> sieve(long long n) {
  std::vector<long long> res(n + 1);
  std::iota(res.begin(), res.end(), 0);
  for (long long i = 2; i * i <= n; ++i) {
    if (res[i] < i) continue;
    for (long long j = i * i; j < n; j += i) {
      if (res[j] == j) res[j] = i;
    }
  }
  return res;
}

std::vector<long long> factor(long long n,
                              const std::vector<long long>& min_factor) {
  std::vector<long long> res;
  while (n > 1) {
    res.push_back(min_factor[n]);
    n /= min_factor[n];
  }
  return res;
}

int main() {
  int a = 10000;
  auto min_factor = sieve(a);
  std::cout << "check 100:" << std::endl;
  for (auto&& res : factor(100, min_factor)) std::cout << res << std::endl;
  std::cout << "check 777:" << std::endl;
  for (auto&& res : factor(777, min_factor)) std::cout << res << std::endl;
}