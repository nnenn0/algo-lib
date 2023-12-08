#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    topological_sort O(|V|+|E|)
    閉路の無い有効グラフ(DAG)についてソートを行う。
    sort: トポロジカルソートを行う。
    get: 結果を返す。
    get_longest_count: 最長経路の長さを返す。閉路が存在する場合-1を返す。
    example: Longest Path
    https://atcoder.jp/contests/dp/tasks/dp_g
*/

using Graph = vector<vector<int>>;

struct TopologicalSort {
  Graph G;
  vector<int> res;
  TopologicalSort(Graph G_) {
    G = G_;
    sort();
  }
  void sort() {
    res = vector<int>();
    int n = int(G.size());
    vector<int> deg(n);
    for (int v = 0; v < n; ++v)
      for (auto& nv : G[v]) deg.at(nv)++;
    queue<int> que;
    for (int i = 0; i < n; ++i)
      if (deg[i] == 0) que.push(i);
    while (!que.empty()) {
      int now = que.front();
      que.pop();
      res.push_back(now);
      for (auto& nv : G[now]) {
        deg.at(nv)--;
        if (deg.at(nv) == 0) que.push(nv);
      }
    }
  }
  vector<int> get() { return res; }
  int get_longest_count() {
    int n = (int)G.size();
    int m = (int)res.size();
    if (n != m) return -1;
    vector<int> dp(n, 0);
    for (auto& v : res)
      for (auto& nv : G[v]) dp[nv] = dp[v] + 1;
    int ret = 0;
    for (int i = 0; i < n; ++i) ret = max(ret, dp[i]);
    return ret;
  }
};

int main() {
  int N, M;
  cin >> N >> M;
  Graph G(N);
  for (int i = 0; i < M; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    G[x].emplace_back(y);
  }
  TopologicalSort ts(G);
  cout << ts.get_longest_count() << endl;
}