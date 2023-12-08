#include <iostream>
#include <vector>

using namespace std;

/*
    group_bit_dp
    集合の組み合わせを求める
    example: Grouping
    https://atcoder.jp/contests/dp/submissions/me
*/

template <class T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

long long N;
long long a[20][20];
long long dp[1 << 16];
long long scores[1 << 16];

void group_bit_dp() {
  for (int used = 0; used < (1 << N); used++) {
    int unused = used ^ ((1 << N) - 1);
    for (int use = unused; use > 0; use = (use - 1) & unused) {
      if (!(use > used)) continue;
      chmax(dp[used | use], dp[used] + scores[use]);
    }
  }
}

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) cin >> a[i][j];
  for (int use = 0; use < (1 << N); ++use) {
    long long score = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = i; j < N; ++j) {
        if (((use >> i) & 1) && ((use >> j) & 1)) {
          score += a[i][j];
        }
      }
    }
    scores[use] = score;
  }

  group_bit_dp();

  cout << dp[(1 << N) - 1] << endl;
}