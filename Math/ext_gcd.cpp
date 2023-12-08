#include <iostream>
#include <numeric>

using namespace std;

/*
    拡張ユークリッドの互除法
    戻り値: aとbの最大公約数
    ax + by = bcd(a, b)を満たす(x, y)が格納される。
    example: ABC186E Throne
    https://atcoder.jp/contests/abc186/tasks/abc186_e
*/

long long ext_gcd(long long a, long long b, long long& x, long long& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long d = ext_gcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

long long solve() {
  long long N, S, K;
  cin >> N >> S >> K;
  long long g = gcd(N, K);
  if (S % g) return -1;
  N /= g, S /= g, K /= g;
  long long x, y;
  ext_gcd(K, N, x, y);
  if (x > 0) {
    x = x - (-x / N + 1) * N;
  }
  x = -x * S;
  return x % N;
}

int main() {
  int T;
  cin >> T;
  while (T--) cout << solve() << endl;
}