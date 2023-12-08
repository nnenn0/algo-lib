#include <iostream>
#include <vector>

using namespace std;

/*
    桁dp
    example: ABC154E Almost Everywhere Zero
    https://atcoder.jp/contests/abc154/tasks/abc154_e
*/

long long dp[111][2][5];
long long digit_dp(string N, int K) {
  int n = int(N.size());
  dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < 2; ++j)
      for (int k = 0; k < K + 1; ++k) {
        int ni = N[i] - '0';
        int lim = j == 0 ? ni : 9;
        for (int x = 0; x <= lim; ++x) {
          int nj = j | (x < lim);
          int nk = k + (x != 0);
          dp[i + 1][nj][nk] += dp[i][j][k];
        }
      }
  return dp[n][0][K] + dp[n][1][K];
}

int main() {
  string N;
  int K;
  cin >> N >> K;
  cout << digit_dp(N, K) << endl;
}