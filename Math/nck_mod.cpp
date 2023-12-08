#include <iostream>
#include <vector>

using namespace std;

/*
    二項係数のための前処理
    init_nCk
    計算量:O(n)
    fact[i]: iの階乗のmod
    fact_inv[i]: iの階乗の逆数のmod
    inv[i]: iの逆数のmod
*/
/*
    MODでの二項係数を求める
    nCk O(1)
    example: ABC145 Knight
    https://atcoder.jp/contests/abc145/tasks/abc145_d
*/

constexpr int MOD = 1000000007;
vector<long long> fact, fact_inv, inv;

void init_nCk(int SIZE) {
  fact.resize(SIZE + 5);
  fact_inv.resize(SIZE + 5);
  inv.resize(SIZE + 5);
  fact[0] = fact[1] = 1;
  fact_inv[0] = fact_inv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < SIZE + 5; i++) {
    fact[i] = fact[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
  }
}

long long nCk(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
}

long long nPk(int n, int k) { return nCk(n, k) * fact[k] % MOD; }

long long nHk(int n, int k) { return nCk(n + k - 1, k); }

long long solve(long long X, long long Y) {
  init_nCk(3000000);
  if ((X + Y) % 3 != 0) return 0;
  long long n = (-X + Y * 2) / 3;
  long long m = (X * 2 - Y) / 3;
  return nCk(n + m, n);
}

int main() {
  long long X, Y;
  cin >> X >> Y;
  cout << solve(X, Y) << endl;
  return 0;
}