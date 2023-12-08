#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
    区間スケジューリング問題 O(NlogN)
    重ならないように区間を選ぶときの最大個数を求める。
    example: キーエンス プログラミング コンテスト 2020 B Robot Arms
    https://atcoder.jp/contests/keyence2020/tasks/keyence2020_b
*/

int main() {
  int N;
  cin >> N;
  vector<int> start_points(N), end_points(N);
  for (int i = 0; i < N; ++i) {
    int x, l;
    cin >> x >> l;
    start_points[i] = x - l;
    end_points[i] = x + l;
  }
  vector<pair<int, int>> p(N);
  for (int i = 0; i < N; ++i) {
    p[i].first = end_points[i];
    p[i].second = start_points[i];
  }
  sort(p.begin(), p.end());  // 終点を優先にソート
  int res = 0;
  int t = -1000100100;
  for (int i = 0; i < N; ++i) {
    if (t <= p[i].second) {
      res++;
      t = p[i].first;
    }
  }
  cout << res << endl;
}