#include <iostream>
#include <vector>

using namespace std;

/*
    LCA(Lowest Common Ancestor)　init: O(NlogN), query: O(logN)
    init: query処理のための前処理
    query: 2点のLCAを求める
    get_dist: 2点の距離を求める
    is_on_path: 2点(u, v)を結ぶパス上にある頂点(a)が存在するか判定する
    example: Single Source Shortest Path
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
*/

using Graph = vector<vector<long long>>;

struct LCA {
  vector<vector<int>> parent;
  vector<int> dist;
  LCA(const Graph &G, int root = 0) { init(G, root); }
  void init(const Graph &G, int root = 0) {
    int V = G.size();
    int K = 1;
    while ((1 << K) < V) K++;
    parent.assign(K, vector<int>(V, -1));
    dist.assign(V, -1);
    dfs(G, root, -1, 0);
    for (int k = 0; k + 1 < K; k++) {
      for (int v = 0; v < V; v++) {
        if (parent[k][v] < 0) {
          parent[k + 1][v] = -1;
        } else {
          parent[k + 1][v] = parent[k][parent[k][v]];
        }
      }
    }
  }
  void dfs(const Graph &G, int v, int p, int d) {
    parent[0][v] = p;
    dist[v] = d;
    for (auto nv : G[v]) {
      if (nv == p) continue;
      dfs(G, nv, v, d + 1);
    }
  }
  int query(int u, int v) {
    if (dist[u] < dist[v]) swap(u, v);
    int K = parent.size();
    for (int k = 0; k < K; k++) {
      if ((dist[u] - dist[v]) >> k & 1) {
        u = parent[k][u];
      }
    }
    if (u == v) return u;
    for (int k = K - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
  int get_dist(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[query(u, v)];
  }
  int get_dist(int u, int v, int w) {
    return (get_dist(u, v) + get_dist(v, w) + get_dist(w, u)) / 2;
  }
  bool is_on_path(int u, int v, int a) {
    return get_dist(u, a) + get_dist(a, v) == get_dist(u, v);
  }
};

int main() {
  int n;
  cin >> n;
  Graph G(n);
  for (int i = 0; i < n; ++i) {
    int k;
    cin >> k;
    for (int j = 0; j < k; ++j) {
      int c;
      cin >> c;
      G[i].push_back(c);
      G[c].push_back(i);
    }
  }
  LCA lca(G);
  vector<int> res;
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;
    res.push_back(lca.query(u, v));
  }
  for (auto &r : res) cout << r << endl;
}