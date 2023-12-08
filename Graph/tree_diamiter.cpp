#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
    tree_diamiter (N)
    木の直径を求める

    example: Diameter of a Tree
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp
*/

struct Edge {
  int to;
  long long cost;
};
using Graph = vector<vector<Edge>>;

pair<long long, int> dfs(const Graph& G, int v, int p) {
  pair<long long, int> ret = make_pair(0LL, v);
  for (auto e : G[v]) {
    if (e.to == p) continue;
    pair<long long, int> next = dfs(G, e.to, v);
    next.first += e.cost;
    ret = max(ret, next);
  }
  return ret;
}

long long tree_diamiter(const Graph& G) {
  pair<long long, int> p = dfs(G, 0, -1);
  pair<long long, int> q = dfs(G, p.second, -1);
  return q.first;
}

int main() {
  int N;
  cin >> N;
  Graph G(N);
  for (int i = 0; i < N - 1; ++i) {
    int s, t, w;
    cin >> s >> t >> w;
    G[s].push_back({t, w});
    G[t].push_back({s, w});
  }
  auto res = tree_diamiter(G);
  cout << res << endl;
}