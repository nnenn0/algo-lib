#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    RollingHash O(N)
    前処理: O(N)
    get: S[left, right)のhash値を取得する
    lcp: S[a:]とT[b:]のlcpを取得する
    example: ABC141E Who Says a Pun?
    https://atcoder.jp/contests/abc141/tasks/abc141_e
*/

struct RollingHash {
  static const int base1 = 1007, base2 = 2009;
  static const int mod1 = 1000000007, mod2 = 1000000009;
  vector<long long> hash1, hash2, power1, power2;

  RollingHash(const string &S) {
    int n = (int)S.size();
    hash1.assign(n + 1, 0);
    hash2.assign(n + 1, 0);
    power1.assign(n + 1, 1);
    power2.assign(n + 1, 1);
    for (int i = 0; i < n; ++i) {
      hash1[i + 1] = (hash1[i] * base1 + S[i]) % mod1;
      hash2[i + 1] = (hash2[i] * base2 + S[i]) % mod2;
      power1[i + 1] = (power1[i] * base1) % mod1;
      power2[i + 1] = (power2[i] * base2) % mod2;
    }
  }

  inline pair<long long, long long> get(int l, int r) const {
    long long res1 = hash1[r] - hash1[l] * power1[r - l] % mod1;
    if (res1 < 0) res1 += mod1;
    long long res2 = hash2[r] - hash2[l] * power2[r - l] % mod2;
    if (res2 < 0) res2 += mod2;
    return {res1, res2};
  }

  inline int getLCP(int a, int b) const {
    int len = min((int)hash1.size() - a, (int)hash1.size() - b);
    int low = 0, high = len;
    while (high - low > 1) {
      int mid = (low + high) >> 1;
      if (get(a, a + mid) != get(b, b + mid))
        high = mid;
      else
        low = mid;
    }
    return low;
  }
};

int main() {
  int n;
  string s;
  cin >> n >> s;
  RollingHash rh(s);
  int res = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int lcp = rh.getLCP(i, j);
      lcp = min(lcp, j - i);
      res = max(res, lcp);
    }
  }
  cout << res << endl;
}