#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    two_pointers_queue queueを使用したしゃくとり法
    O(N)
    example: ABC032C 列
    https://atcoder.jp/contests/abc032/tasks/abc032_c
*/

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      cout << n << endl;
      return 0;
    }
  }
  int res = 0;
  long long p = 1;
  queue<int> q;
  for (auto ai : a) {
    q.push(ai);
    p *= ai;
    while (q.size() && p > k) {
      int rm = q.front();
      q.pop();
      p /= rm;
    }
    res = max(res, int(q.size()));
  }
  cout << res << endl;
}