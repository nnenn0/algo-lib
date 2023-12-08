#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    arithmetic_progression_sum
    等差数列の和を求める
    a: 初項, d: 等差, n: 項数
    example: ABC216E Amusement Park
    https://atcoder.jp/contests/abc216/tasks/abc216_e
*/

template <class T>
T arithmetic_progression_sum(T a, T d, long long n) {
  return (a * 2 + d * (n - 1)) * n / 2;
}

int main() {
  int N;
  long long K;
  cin >> N >> K;
  vector<long long> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  A.push_back(0);
  sort(A.rbegin(), A.rend());
  long long res = 0;
  for (int i = 0; i < N; ++i) {
    long long diff = A[i] - A[i + 1];
    long long cnt = 1LL * diff * (i + 1);
    if (cnt <= K) {
      K -= cnt;
      res += arithmetic_progression_sum(A[i], -1LL, diff) * (i + 1);
    } else {
      long long d = K / (i + 1);
      long long m = K % (i + 1);
      res += arithmetic_progression_sum(A[i], -1LL, d) * (i + 1);
      res += (A[i] - d) * m;
      K = 0;
    }
  }
  cout << res << endl;
  return 0;
}