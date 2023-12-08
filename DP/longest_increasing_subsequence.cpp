#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    LIS O(NlogN)
    最長増加部分列(LIS)を求める
    is_strong = falseの時同じ値が連続することを許す
    example: Longest Increasing Subsequence
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=jp
*/

constexpr int INF = 1000100100;

int LIS(const vector<int>& vec, bool is_strong = true) {
  int n = int(vec.size());
  vector<int> dp(n, INF);
  for (auto& v : vec) {
    if (is_strong)
      *lower_bound(dp.begin(), dp.end(), v) = v;
    else
      *upper_bound(dp.begin(), dp.end(), v) = v;
  }
  return int(lower_bound(dp.begin(), dp.end(), INF) - dp.begin());
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  cout << LIS(a) << endl;
}