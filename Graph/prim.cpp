#include <iostream>
#include <vector>

using namespace std;

/*
    プリム法 O(|V|^2)
    最小全域木の重みの総和を求める。
    example: Minimum Spanning Tree
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_12_A&lang=jp
*/
struct Prim {
  const int INF = 1e9;
  int sum;
  int n;
  vector<int> mincost;
  vector<bool> used;
  Prim(vector<vector<int>> const& Graph) {
    n = (int)Graph.size();
    mincost.assign(n, INF);
    used.assign(n, false);
    sum = 0;
    mincost[0] = 0;
    while (true) {
      int v = -1;
      for (int u = 0; u < n; u++) {
        if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
      }
      if (v == -1) break;
      used[v] = true;
      sum += mincost[v];
      for (int u = 0; u < n; u++) {
        if (Graph[v][u] != -1) mincost[u] = min(mincost[u], Graph[v][u]);
      }
    }
  }
};

vector<vector<int>> G;

int main() {
  int N;
  cin >> N;
  vector<vector<int>> G(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> G[i][j];
    }
  }
  Prim prim(G);
  cout << prim.sum << endl;
  return 0;
}